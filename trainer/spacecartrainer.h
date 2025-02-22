#ifndef SPACECARTRAINER_H
#define SPACECARTRAINER_H

#include "trainer.h"

class SpaceCarTrainer : public Trainer
{
public:
    SpaceCarTrainer(ProcessMonitor *monitor);
    virtual ~SpaceCarTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // SPACECARTRAINER_H
