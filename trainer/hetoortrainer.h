#ifndef HETOORTRAINER_H
#define HETOORTRAINER_H

#include "trainer.h"

class HetoorTrainer : public Trainer
{
public:
    explicit HetoorTrainer(ProcessMonitor *monitor);
    virtual ~HetoorTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;

private:
    bool ApplyMagmaDamageLock(HANDLE hProcess, uintptr_t moduleBase);     // 岩浆伤害锁定
    bool RestoreMagmaDamageLock(HANDLE hProcess, uintptr_t moduleBase);   // 恢复岩浆伤害
    bool ApplyMonsterDamageLock(HANDLE hProcess, uintptr_t moduleBase);   // 怪物伤害锁定
    bool RestoreMonsterDamageLock(HANDLE hProcess, uintptr_t moduleBase); // 恢复怪物伤害
};

#endif // HETOORTRAINER_H
