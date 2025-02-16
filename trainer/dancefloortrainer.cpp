#include "dancefloortrainer.h"

DanceFloorTrainer::DanceFloorTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool DanceFloorTrainer::applyModification()
{
    // 地址：GameAssembly.dll+3A589E，替换为 nop 指令
    uintptr_t patchAddress = moduleBase + 0x3A589E;
    qDebug() << L"Applying dance score lock at address: 0x" << patchAddress;
    BYTE patchBytes[7] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; // nop x7
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool DanceFloorTrainer::restoreModification()
{
    // 地址：GameAssembly.dll+3A589E，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x3A589E;
    qDebug() << L"Restoring dance score lock at address: 0x" << patchAddress;
    BYTE originalBytes[7] = {0x83, 0x87, 0xD4, 0x00, 0x00, 0x00, 0x01}; // add dword ptr [rdi+000000D4],01
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
