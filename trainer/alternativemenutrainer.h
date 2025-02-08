#ifndef ALTERNATIVEMENUTRAINER_H
#define ALTERNATIVEMENUTRAINER_H

#include "trainer.h"

class AlternativeMenuTrainer : public Trainer
{
public:
    AlternativeMenuTrainer(ProcessMonitor *monitor);
    virtual ~AlternativeMenuTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // ALTERNATIVEMENUTRAINER_H
