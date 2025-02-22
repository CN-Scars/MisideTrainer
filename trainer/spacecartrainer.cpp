#include "spacecartrainer.h"

SpaceCarTrainer::SpaceCarTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool SpaceCarTrainer::applyModification()
{
    // 地址：GameAssembly.dll+4FAE18，替换为 nop 指令
    uintptr_t patchAddress = moduleBase + 0x4FAE18;
    qDebug() << L"Applying Space Car always first place at address: 0x" << patchAddress;
    BYTE patchBytes[3] = {0x90, 0x90, 0x90}; // nop x3
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool SpaceCarTrainer::restoreModification()
{
    // 地址：GameAssembly.dll+4FAE18，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x4FAE18;
    qDebug() << L"Restoring Space Car always first place at address: 0x" << patchAddress;
    BYTE originalBytes[3] = {0xFF, 0x47, 0x18}; // inc [rdi+18]
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
