#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "manager/trainermanager.h"

#include <QDesktopServices>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class TrainerManager;

typedef struct
{
    QString iconUrl;    // 网站的图标 URL
    QString author;     // 作者名称
    QString publishUrl; // 网站的 URL
    QString profileUrl; // 作者个人资料 URL
} WebsiteInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onProcessFoundChanged(bool found);
    void onModuleFoundChanged(bool found);

private slots:
    void onAlternativeMenuUnlockPushButtonClicked();

    void onGameConsoleInvincibilityPushButtonClicked();

    void onDairyScandalInvincibilityAndInstantKillPushButtonClicked();

    void onDecreaseMitaSnowballsPushButtonClicked();

    void onLockScoreOfMitaInDanceFloorPushButtonClicked();

    void onSpaceCarAlwaysFirstPlacePushButtonClicked();

    void onSpaceCarBossNeverHurtsYouPushButtonClicked();

    void onHetoorHealthLockPushButtonClicked();

    void onQuadRangleNoCollisionPushButtonClicked();

private:
    Ui::MainWindow *ui;
    QTranslator *appTranslator = nullptr;
    TrainerManager *trainerManager;
    bool processFound = false;
    bool moduleFound = false;
    QMap<QPushButton *, bool> pushButtonEnabled;

    void initPushButton();
    void initPushButtonConnections();
    void initLanguageAction();
    void initAboutAction();
    void initTextLabels();
    void switchLanguage(const QString &langCode);
    void handleProcessAndModuleStateChange();
    void updatePictureLabel();
    void updatePushButtonText();
    void resetPushButtonState();
    void createAboutInfoSection(QDialog *dialog, QVBoxLayout *sectionLayout, const WebsiteInfo &info);
};
#endif // MAINWINDOW_H
