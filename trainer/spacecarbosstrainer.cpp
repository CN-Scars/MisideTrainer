#include "spacecarbosstrainer.h"

SpaceCarBossTrainer::SpaceCarBossTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool SpaceCarBossTrainer::applyModification()
{
    // 地址：GameAssembly.dll+4F6724，替换为 nop 指令
    uintptr_t patchAddress = moduleBase + 0x4F6724 + 1;
    qDebug() << L"Applying Space Car boss never hurts you at address: 0x" << patchAddress;
    BYTE patchBytes[1] = {0x84}; // je
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool SpaceCarBossTrainer::restoreModification()
{
    // 地址：GameAssembly.dll+4F6724，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x4F6724 + 1;
    qDebug() << L"Restoring Space Car boss never hurts you at address: 0x" << patchAddress;
    BYTE originalBytes[1] = {0x85}; // jne
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
