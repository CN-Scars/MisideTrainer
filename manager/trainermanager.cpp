#include "trainermanager.h"

TrainerManager::TrainerManager(QObject *parent) : QObject{parent}, mainWindow(nullptr) {}

TrainerManager::~TrainerManager()
{
    for (const auto &trainer : std::as_const(trainerSelector))
    {
        trainer->restoreModification();
        delete trainer;
    }
    delete monitor;
}

void TrainerManager::setUp(MainWindow *mainWindow)
{
    // 绑定 MainWindow 对象
    this->mainWindow = mainWindow;
    // 初始化 ProcessMonitor 对象
    monitor = new ProcessMonitor("MiSideFull.exe", "GameAssembly.dll", this);
    connect(monitor, &ProcessMonitor::processFoundChanged, mainWindow, &MainWindow::onProcessFoundChanged);
    connect(monitor, &ProcessMonitor::moduleFoundChanged, mainWindow, &MainWindow::onModuleFoundChanged);

    monitor->startMonitoring();

    alternativeMenuTrainer = new AlternativeMenuTrainer(monitor);
    gameConsoleTrainer = new GameConsoleTrainer(monitor);
    dairyScandalTrainer = new DairyScandalTrainer(monitor);
    penguinPilesTrainer = new PenguinPilesTrainer(monitor);
    spaceCarTrainer = new SpaceCarTrainer(monitor);
    spaceCarBossTrainer = new SpaceCarBossTrainer(monitor);
    danceFloorTrainer = new DanceFloorTrainer(monitor);
    hetoorTrainer = new HetoorTrainer(monitor);
    quadRangleTrainer = new QuadRangleTrainer(monitor);

    trainerSelector[TrainerType::AlternativeMenu] = alternativeMenuTrainer;
    trainerSelector[TrainerType::GameConsole] = gameConsoleTrainer;
    trainerSelector[TrainerType::DairyScandal] = dairyScandalTrainer;
    trainerSelector[TrainerType::PenguinPiles] = penguinPilesTrainer;
    trainerSelector[TrainerType::SpaceCar] = spaceCarTrainer;
    trainerSelector[TrainerType::SpaceCarBoss] = spaceCarBossTrainer;
    trainerSelector[TrainerType::DanceFloor] = danceFloorTrainer;
    trainerSelector[TrainerType::Hetoor] = hetoorTrainer;
    trainerSelector[TrainerType::QuadRangle] = quadRangleTrainer;
}

bool TrainerManager::useTrainer(TrainerType type, QPushButton *button)
{
    return onTrainerButtonClicked(trainerSelector[type], button);
}

void TrainerManager::resetTrainers()
{
    for (const auto &trainer : std::as_const(trainerSelector))
        trainer->setModificationState(false);
}

bool TrainerManager::onTrainerButtonClicked(Trainer *trainer, QPushButton *button)
{
    if (trainer->modificationIsEnabled())
    {
        bool restoreResult = trainer->restoreModification();
        if (restoreResult)
        {
            trainer->setModificationState(false);
            button->setText(tr("Enable"));
        }
        else
        {
            QMessageBox::warning(mainWindow, tr("Warning"), tr("Restore failed"));
            return false;
        }
    }
    else
    {
        bool applyResult = trainer->applyModification();
        if (applyResult)
        {
            trainer->setModificationState(true);
            button->setText(tr("Disable"));
        }
        else
        {
            QMessageBox::warning(mainWindow, tr("Warning"), tr("Apply failed"));
            return false;
        }
    }

    return true;
}
