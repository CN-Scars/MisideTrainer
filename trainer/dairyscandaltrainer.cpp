#include "dairyscandaltrainer.h"

DairyScandalTrainer::DairyScandalTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool DairyScandalTrainer::applyModification()
{
    // 地址：GameAssembly.dll+39125A，替换为跳转指令
    uintptr_t patchAddress = moduleBase + 0x39125A;
    // 地址：GameAssembly.dll+391262，注入代码结束回退的地址（指令：jna GameAssembly.dll+39126E）
    uintptr_t returnAddress = moduleBase + 0x391262;
    qDebug() << L"Applying kill lock at address: 0x" << patchAddress;

    // 1. 分配内存（为注入代码分配28字节）
    newMem = (LPVOID)(moduleBase - 0x28);
    // 分配28字节
    newMem = VirtualAllocEx(hProcess, newMem, 28, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!newMem)
    {
        qDebug() << L"Failed to allocate memory in target process.";
        return false;
    }

    // 计算从 injectCode[0x17]（第5条指令首地址） 到 returnAddress 的偏移量
    int32_t jmpOffsetToReturn = static_cast<int32_t>(returnAddress - (uintptr_t)newMem - 0x17 - 0x5);
    BYTE injectCode[28] = {
        0x83, 0x7B, 0x20, 0x00,                         // cmp dword ptr [rbx+20],00
        0x0F, 0x85, 0x05, 0x00, 0x00, 0x00,             // jne (next addr of codes that modify HP)
        0xE9, 0x08, 0x00, 0x00, 0x00,                   // jmp to end of code
        0xF3, 0x0F, 0x11, 0x8B, 0x90, 0x00, 0x00, 0x00, // movss [rbx+00000090],xmm1
        0xE9, 0x00, 0x00, 0x00, 0x00,                   // jmp GameAssembly.dll+391262 (Undone)
    };
    memcpy(&injectCode[24], &jmpOffsetToReturn, sizeof(jmpOffsetToReturn));
    // 输出注入代码的首地址
    qDebug() << L"Injecting code at address: 0x" << (uintptr_t)newMem;

    // 3. 将代码写入目标进程
    if (!WriteProcessMemory(hProcess, newMem, injectCode, sizeof(injectCode), NULL))
    {
        qDebug() << L"Failed to write injected code to target process.";
        VirtualFreeEx(hProcess, newMem, 0, MEM_RELEASE);
        return false;
    }

    // 4. 修改原始代码，使其跳转到注入代码（GameAssembly.dll+39125A 位置处的 jmp 指令）
    BYTE jumpPatch[8] = {0};
    jumpPatch[0] = 0xE9;                                                              // jmp to injected code
    int32_t jmpOffset = static_cast<int32_t>((uintptr_t)newMem - (patchAddress + 5)); // 计算跳转偏移
    // 输出跳转偏移
    qDebug() << L"Jump offset: 0x" << jmpOffset;
    memcpy(&jumpPatch[1], &jmpOffset, sizeof(jmpOffset)); // 填写偏移量

    // 5. 填充跳转后空缺部分，使用 nop 填充至下一条指令（nop 0F 1F 00）
    jumpPatch[5] = 0x0F;
    jumpPatch[6] = 0x1F;
    jumpPatch[7] = 0x00;

    // 6. 写入跳转补丁
    if (!ApplyPatch(hProcess, patchAddress, jumpPatch, sizeof(jumpPatch)))
    {
        qDebug() << L"Failed to apply jump patch for snowball lock.";
        VirtualFreeEx(hProcess, newMem, 0, MEM_RELEASE);
        return false;
    }

    return true;
}

bool DairyScandalTrainer::restoreModification()
{
    // 清空注入的代码
    if (!VirtualFreeEx(hProcess, newMem, 0, MEM_RELEASE))
    {
        qDebug() << L"Failed to free memory at address: 0x" << (uintptr_t)newMem << " in target process.";
        return false;
    }
    newMem = nullptr;

    uintptr_t patchAddress = moduleBase + 0x39125A;
    qDebug() << L"Restoring original code at address: 0x" << patchAddress;

    /* 还原原始的movss指令：
    Address                   Bytes                   Opcode
    GameAssembly.dll+39125A - F3 0F11 8B 90000000   - movss [rbx+00000090],xmm1
    GameAssembly.dll+391262 - 76 0A                 - jna GameAssembly.dll+39126E
    */
    BYTE originalBytes[10] = {
        0xF3, 0x0F, 0x11, 0x8B, 0x90, 0x00, 0x00, 0x00, // movss [rbx+00000090],xmm1
        0x76, 0x0A                                      // jna GameAssembly.dll+39126E
    };
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
