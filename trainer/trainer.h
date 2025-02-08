#ifndef TRAINER_H
#define TRAINER_H

#include "utils/processmonitor.h"

#include <windows.h>
#include <tlhelp32.h>
#include <QDebug>

class Trainer : public QObject
{
    Q_OBJECT

public:
    explicit Trainer(ProcessMonitor *monitor);
    virtual ~Trainer() {}

    HANDLE getProcessHandle() const;
    uintptr_t getModuleBase() const;
    bool modificationIsEnabled() const;
    void setModificationState(bool enabled);
    /**
     * @brief 通用的内存补丁函数
     *
     * @param hProcess 目标进程句柄
     * @param patchAddress 补丁地址
     * @param patchBytes 要写入的字节数组
     * @param patchSize 字节数组大小
     * @return true 成功写入补丁
     * @return false 写入失败
     */
    bool ApplyPatch(HANDLE hProcess, uintptr_t patchAddress, const BYTE *patchBytes, size_t patchSize);

    // 抽象方法：子类实现具体的修改和恢复逻辑
    virtual bool applyModification() = 0;
    virtual bool restoreModification() = 0;

public slots:
    void updateProcessState(bool processFound);
    void updateModuleState(bool moduleFound);

protected:
    ProcessMonitor *monitor;
    HANDLE hProcess;
    uintptr_t moduleBase;
    bool modificationEnabled;
};

#endif // TRAINER_H
