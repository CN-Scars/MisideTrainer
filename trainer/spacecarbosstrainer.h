#ifndef SPACECARBOSSTRAINER_H
#define SPACECARBOSSTRAINER_H

#include "trainer.h"

class SpaceCarBossTrainer : public Trainer
{
public:
    SpaceCarBossTrainer(ProcessMonitor *monitor);
    virtual ~SpaceCarBossTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // SPACECARBOSSTRAINER_H
