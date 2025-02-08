#include "trainer.h"

Trainer::Trainer(ProcessMonitor *monitor) : monitor(monitor), hProcess(NULL), moduleBase(0), modificationEnabled(false)
{
    // 首次构造Trainer对象时，需要手动从ProcessMonitor对象中获取句柄和基址
    hProcess = monitor->getProcessHandle();
    moduleBase = monitor->getModuleBase();
    // 连接ProcessMonitor的信号与对应的槽函数，实现句柄和基址的同步更新
    connect(monitor, &ProcessMonitor::processFoundChanged, this, &Trainer::updateProcessState);
    connect(monitor, &ProcessMonitor::moduleFoundChanged, this, &Trainer::updateModuleState);
}

HANDLE Trainer::getProcessHandle() const
{
    return hProcess;
}

uintptr_t Trainer::getModuleBase() const
{
    return moduleBase;
}

bool Trainer::modificationIsEnabled() const
{
    return modificationEnabled;
}

void Trainer::setModificationState(bool enabled)
{
    modificationEnabled = enabled;
}

bool Trainer::ApplyPatch(HANDLE hProcess, uintptr_t patchAddress, const BYTE *patchBytes, size_t patchSize)
{
    DWORD oldProtect;
    if (!VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(patchAddress), patchSize, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        qDebug() << "VirtualProtectEx failed";
        return false;
    }

    SIZE_T bytesWritten;
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(patchAddress), patchBytes, patchSize, &bytesWritten))
    {
        qDebug() << "WriteProcessMemory failed";
        VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(patchAddress), patchSize, oldProtect, &oldProtect);
        return false;
    }

    VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(patchAddress), patchSize, oldProtect, &oldProtect);
    return true;
}

void Trainer::updateProcessState(bool processFound)
{
    if (processFound)
    {
        hProcess = monitor->getProcessHandle(); // 获取进程句柄
    }
    else
    {
        hProcess = NULL; // 如果进程未找到，清空句柄
    }

    qDebug() << "更新了Trainer的进程句柄：" << hProcess;
}

void Trainer::updateModuleState(bool moduleFound)
{
    qDebug() << "接收到了moduleFoundChanged信号";
    if (moduleFound)
    {
        moduleBase = monitor->getModuleBase(); // 获取模块基址
    }
    else
    {
        moduleBase = 0; // 如果模块未找到，清空基址
    }

    qDebug() << "更新了模块基址：" << QString("0x").append(QString::number(moduleBase, 16));
}
