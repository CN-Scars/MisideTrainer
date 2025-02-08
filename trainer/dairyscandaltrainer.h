#ifndef DAIRYSCANDALTRAINER_H
#define DAIRYSCANDALTRAINER_H

#include "trainer.h"

class DairyScandalTrainer : public Trainer
{
public:
    explicit DairyScandalTrainer(ProcessMonitor *monitor);
    virtual ~DairyScandalTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;

private:
    LPVOID newMem = nullptr; // 为注入代码分配的内存地址
};

#endif // DAIRYSCANDALTRAINER_H
