#include "quadrangletrainer.h"

QuadRangleTrainer::QuadRangleTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool QuadRangleTrainer::applyModification()
{
    // 地址：GameAssembly.dll+30C497，替换为 jne
    uintptr_t patchAddress = moduleBase + 0x30C497 + 1;
    qDebug() << L"Applying QuadRangle no collision address: 0x" << patchAddress;
    BYTE patchBytes[1] = {0x85}; // jne
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool QuadRangleTrainer::restoreModification()
{
    // 地址：GameAssembly.dll+30C497，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x30C497 + 1;
    qDebug() << L"Restoring QuadRangle no collision address: 0x" << patchAddress;
    BYTE originalBytes[1] = {0x84}; // je
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
