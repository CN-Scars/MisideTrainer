#ifndef DANCEFLOORTRAINER_H
#define DANCEFLOORTRAINER_H

#include "trainer.h"

class DanceFloorTrainer : public Trainer
{
public:
    DanceFloorTrainer(ProcessMonitor *monitor);
    virtual ~DanceFloorTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // DANCEFLOORTRAINER_H
