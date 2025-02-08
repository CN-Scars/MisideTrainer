#ifndef PENGUINPILESTRAINER_H
#define PENGUINPILESTRAINER_H

#include "trainer.h"

class PenguinPilesTrainer : public Trainer
{
public:
    explicit PenguinPilesTrainer(ProcessMonitor *monitor);
    virtual ~PenguinPilesTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // PENGUINPILESTRAINER_H
