#include "processmonitor.h"

ProcessMonitor::ProcessMonitor(const QString &processName, const QString &moduleName, QObject *parent)
    : QObject(parent), targetProcessName(processName), targetModuleName(moduleName),
      targetProcessID(0), hProcess(nullptr), targetModuleBase(0) {}

ProcessMonitor::~ProcessMonitor()
{
    CloseHandle(hProcess);
}

void ProcessMonitor::startMonitoring()
{
    bool processFound = checkProcess();
    bool moduleFound = checkModule();

    printStatus(processFound, moduleFound);

    // 通过定时器持续检查
    QTimer::singleShot(2000, this, &ProcessMonitor::startMonitoring);
}

HANDLE ProcessMonitor::getProcessHandle() const
{
    return hProcess;
}

uintptr_t ProcessMonitor::getModuleBase() const
{
    return targetModuleBase;
}

bool ProcessMonitor::checkProcess()
{
    targetProcessID = GetProcessID(targetProcessName.toStdWString());
    return targetProcessID != 0;
}

bool ProcessMonitor::checkModule()
{
    if (targetProcessID == 0)
    {
        return false;
    }
    targetModuleBase = GetModuleBaseAddress(targetProcessID, targetModuleName.toStdWString());
    return targetModuleBase != 0;
}

void ProcessMonitor::printStatus(bool processFound, bool moduleFound)
{
    static bool lastProcessFound = false;
    static bool lastModuleFound = false;

    if (processFound != lastProcessFound)
    {
        lastProcessFound = processFound;
        // 更新进程句柄
        if (targetProcessID != 0)
        {
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetProcessID);
        }
        else
        {
            hProcess = nullptr;
        }
        qDebug() << (processFound ? "Process found:" : "Process not found:") << targetProcessName;
        emit processFoundChanged(processFound);

        qDebug() << "触发了信号 processFoundChanged";
        qDebug() << "更新了ProcessMonitor的进程句柄：" << hProcess;
    }

    if (moduleFound != lastModuleFound)
    {
        lastModuleFound = moduleFound;
        qDebug() << (moduleFound ? "Module found:" : "Module not found:") << QString("0x").append(QString::number(targetModuleBase, 16));
        emit moduleFoundChanged(moduleFound);
        qDebug() << "触发了信号 moduleFoundChanged";
    }
}

DWORD ProcessMonitor::GetProcessID(const std::wstring &processName)
{
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(hSnapshot, &pe))
    {
        do
        {
            if (processName == pe.szExeFile)
            {
                processID = pe.th32ProcessID;
                break;
            }
        } while (Process32NextW(hSnapshot, &pe));
    }
    CloseHandle(hSnapshot);
    return processID;
}

uintptr_t ProcessMonitor::GetModuleBaseAddress(DWORD processID, const std::wstring &moduleName)
{
    uintptr_t moduleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32W me;
    me.dwSize = sizeof(me);
    if (Module32FirstW(hSnapshot, &me))
    {
        do
        {
            if (moduleName == me.szModule)
            {
                moduleBaseAddress = reinterpret_cast<uintptr_t>(me.modBaseAddr);
                break;
            }
        } while (Module32NextW(hSnapshot, &me));
    }
    CloseHandle(hSnapshot);
    return moduleBaseAddress;
}
