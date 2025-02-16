#include "penguinpilestrainer.h"

PenguinPilesTrainer::PenguinPilesTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool PenguinPilesTrainer::applyModification()
{
    // 使用dec指令替换inc指令，让雪球的数量递减
    uintptr_t patchAddress = moduleBase + 0x38938C;
    qDebug() << L"Applying snowball dec lock at address: 0x" << patchAddress;
    BYTE patchBytes[6] = {0xFF, 0x8B, 0xE4, 0x00, 0x00, 0x00}; // dec [rbx+0xE4]
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool PenguinPilesTrainer::restoreModification()
{
    // 恢复原始的inc指令
    uintptr_t patchAddress = moduleBase + 0x38938C;
    qDebug() << L"Restoring snowball lock at address: 0x" << patchAddress;
    BYTE originalBytes[6] = {0xFF, 0x83, 0xE4, 0x00, 0x00, 0x00}; // inc [rbx+0xE4]
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
