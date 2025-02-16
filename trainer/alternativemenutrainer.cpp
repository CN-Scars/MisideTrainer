#include "alternativemenutrainer.h"

AlternativeMenuTrainer::AlternativeMenuTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool AlternativeMenuTrainer::applyModification()
{
    // 地址GameAssembly.dll+4B4BF9，替换为nop指令
    uintptr_t patchAddress = moduleBase + 0x4B4BF9;
    qDebug() << L"Applying alternative menu unlock at address: 0x" << patchAddress;
    BYTE patchBytes[2] = {0x90, 0x90}; // nop x2
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool AlternativeMenuTrainer::restoreModification()
{
    // 地址GameAssembly.dll+4B4BF9，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x4B4BF9;
    qDebug() << L"Restoring alternative menu unlock at address: 0x" << patchAddress;
    BYTE originalBytes[2] = {0x75, 0x0A}; // jne GameAssembly.dll+4A4BE5
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
