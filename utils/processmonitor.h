#ifndef PROCESSMONITOR_H
#define PROCESSMONITOR_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QTimer>
#include <windows.h>
#include <tlhelp32.h>

class ProcessMonitor : public QObject
{
    Q_OBJECT

public:
    explicit ProcessMonitor(const QString &processName, const QString &moduleName, QObject *parent = nullptr);
    ~ProcessMonitor();

    void startMonitoring();
    HANDLE getProcessHandle() const;
    uintptr_t getModuleBase() const;

private:
    QString targetProcessName;
    QString targetModuleName;
    DWORD targetProcessID;
    HANDLE hProcess;
    uintptr_t targetModuleBase;

    bool checkProcess();
    bool checkModule();
    void printStatus(bool processFound, bool moduleFound);
    DWORD GetProcessID(const std::wstring &processName);
    uintptr_t GetModuleBaseAddress(DWORD processID, const std::wstring &moduleName);

signals:
    void processFoundChanged(bool found);
    void moduleFoundChanged(bool found);
};

#endif // PROCESSMONITOR_H
