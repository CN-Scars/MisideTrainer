#ifndef GAMECONSOLETRAINER_H
#define GAMECONSOLETRAINER_H

#include "trainer.h"

class GameConsoleTrainer : public Trainer
{
public:
    GameConsoleTrainer(ProcessMonitor *monitor);
    virtual ~GameConsoleTrainer() {}

    virtual bool applyModification() override;
    virtual bool restoreModification() override;
};

#endif // GAMECONSOLETRAINER_H
