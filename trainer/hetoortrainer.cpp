#include "hetoortrainer.h"

HetoorTrainer::HetoorTrainer(ProcessMonitor *monitor) : Trainer(monitor) {}

bool HetoorTrainer::applyModification()
{
    bool magmaSuccess = ApplyMagmaDamageLock(hProcess, moduleBase);
    bool monsterSuccess = ApplyMonsterDamageLock(hProcess, moduleBase);
    return magmaSuccess && monsterSuccess;
}

bool HetoorTrainer::restoreModification()
{
    bool magmaSuccess = RestoreMagmaDamageLock(hProcess, moduleBase);
    bool monsterSuccess = RestoreMonsterDamageLock(hProcess, moduleBase);
    return magmaSuccess && monsterSuccess;
}

bool HetoorTrainer::ApplyMagmaDamageLock(HANDLE hProcess, uintptr_t moduleBase)
{
    // 地址：GameAssembly.dll + 0x525A78, 补丁字节：NOP x5
    uintptr_t patchAddress = moduleBase + 0x525A78;
    qDebug() << L"Applying magma patch at address: 0x" << patchAddress;
    BYTE patchBytes[5] = {0x90, 0x90, 0x90, 0x90, 0x90};
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool HetoorTrainer::RestoreMagmaDamageLock(HANDLE hProcess, uintptr_t moduleBase)
{
    // 原始字节：F3 0F 11 77 18
    uintptr_t patchAddress = moduleBase + 0x525A78;
    qDebug() << L"Restoring magma patch at address: 0x" << patchAddress;
    BYTE originalBytes[5] = {0xF3, 0x0F, 0x11, 0x77, 0x18};
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}

bool HetoorTrainer::ApplyMonsterDamageLock(HANDLE hProcess, uintptr_t moduleBase)
{
    // 地址：GameAssembly.dll + 0x524D87, 补丁字节：NOP x5
    uintptr_t patchAddress = moduleBase + 0x524D87;
    qDebug() << L"Applying monster patch at address: 0x" << patchAddress;
    BYTE patchBytes[5] = {0x90, 0x90, 0x90, 0x90, 0x90};
    return ApplyPatch(hProcess, patchAddress, patchBytes, sizeof(patchBytes));
}

bool HetoorTrainer::RestoreMonsterDamageLock(HANDLE hProcess, uintptr_t moduleBase)
{
    // 原始字节：F3 0F 11 53 18
    uintptr_t patchAddress = moduleBase + 0x524D87;
    qDebug() << L"Restoring monster patch at address: 0x" << patchAddress;
    BYTE originalBytes[5] = {0xF3, 0x0F, 0x11, 0x53, 0x18};
    return ApplyPatch(hProcess, patchAddress, originalBytes, sizeof(originalBytes));
}
