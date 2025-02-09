#ifndef TRAINERMANAGER_H
#define TRAINERMANAGER_H

#pragma once

#include "ui/mainwindow.h"
#include "trainer/trainer.h"
#include "trainer/alternativemenutrainer.h"
#include "trainer/dairyscandaltrainer.h"
#include "trainer/dancefloortrainer.h"
#include "trainer/hetoortrainer.h"
#include "trainer/penguinpilestrainer.h"
#include "utils/processmonitor.h"

#include <QMap>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>

class MainWindow;

enum class TrainerType
{
    AlternativeMenu,
    DairyScandal,
    PenguinPiles,
    DanceFloor,
    Hetoor
};

class TrainerManager : public QObject
{
    Q_OBJECT

public:
    explicit TrainerManager(QObject *parent = nullptr);
    ~TrainerManager();

    void setUp(MainWindow *mainWindow);
    bool useTrainer(TrainerType type, QPushButton *button); // 使用指定修改器
    void resetTrainers();                                   // 重置所有修改器

private:
    MainWindow *mainWindow;
    ProcessMonitor *monitor;
    AlternativeMenuTrainer *alternativeMenuTrainer;
    DairyScandalTrainer *dairyScandalTrainer;
    PenguinPilesTrainer *penguinPilesTrainer;
    DanceFloorTrainer *danceFloorTrainer;
    HetoorTrainer *hetoorTrainer;
    QMap<TrainerType, Trainer *> trainerSelector;

    bool onTrainerButtonClicked(Trainer *trainer, QPushButton *button); // 通用修改器按钮点击事件处理
};

#endif // TRAINERMANAGER_H
