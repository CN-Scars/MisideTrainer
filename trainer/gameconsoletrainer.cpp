#include "gameconsoletrainer.h"

GameConsoleTrainer::GameConsoleTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool GameConsoleTrainer::applyModification()
{
    // 地址：GameAssembly.dll+30EF2D，替换为nop x5
    uintptr_t patchAddress = moduleBase + 0x30EF2D;
    qDebug() << L"Applying game console invincibility at address: 0x" << patchAddress;
    BYTE patchBytes[5] = {0x90, 0x90, 0x90, 0x90, 0x90};    // nop x5
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool GameConsoleTrainer::restoreModification()
{
    // 地址：GameAssembly.dll+30EF2D，恢复原始指令
    uintptr_t patchAddress = moduleBase + 0x30EF2D;
    qDebug() << L"Restoring game console invincibility at address: 0x" << patchAddress;
    BYTE originalBytes[5] = {0xE8, 0xBE, 0xDC, 0xFF, 0xFF};  // call TetrisGame.Death
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
