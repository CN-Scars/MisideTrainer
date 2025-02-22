#ifndef QUADRANGLETRAINER_H
#define QUADRANGLETRAINER_H

#include "trainer.h"

class QuadRangleTrainer : public Trainer
{
public:
    QuadRangleTrainer(ProcessMonitor *monitor);
    virtual ~QuadRangleTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // QUADRANGLETRAINER_H
