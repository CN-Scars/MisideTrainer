#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), trainerManager(new TrainerManager)
{
    ui->setupUi(this);
    initPushButton();
    initLanguageAction();
    initAboutAction();
    initTextLabels();
    updatePictureLabel();
    trainerManager->setUp(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trainerManager;
}

void MainWindow::onProcessFoundChanged(bool found)
{
    processFound = found;
    handleProcessAndModuleStateChange();
}

void MainWindow::onModuleFoundChanged(bool found)
{
    moduleFound = found;
    handleProcessAndModuleStateChange();
}

void MainWindow::onAlternativeMenuUnlockPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::AlternativeMenu, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onGameConsoleInvincibilityPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::GameConsole, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onDairyScandalInvincibilityAndInstantKillPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::DairyScandal, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onDecreaseMitaSnowballsPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::PenguinPiles, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onLockScoreOfMitaInDanceFloorPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::DanceFloor, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onSpaceCarAlwaysFirstPlacePushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::SpaceCar, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onSpaceCarBossNeverHurtsYouPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::SpaceCarBoss, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onHetoorHealthLockPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::Hetoor, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::onQuadRangleNoCollisionPushButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool success = trainerManager->useTrainer(TrainerType::QuadRangle, button);
    if (success)
    {
        pushButtonEnabled[button] = !pushButtonEnabled[button];
        button->setText(pushButtonEnabled[button] ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::initPushButton()
{
    initPushButtonConnections();

    pushButtonEnabled = {
        {ui->alternativeMenuUnlockPushButton, false},
        {ui->gameConsoleInvincibilityPushButton, false},
        {ui->dairyScandalInvincibilityAndInstantKillPushButton, false},
        {ui->decreaseMitaSnowballsPushButton, false},
        {ui->lockScoreOfMitaInDanceFloorPushButton, false},
        {ui->spaceCarAlwaysFirstPlacePushButton, false},
        {ui->spaceCarBossNeverHurtsYouPushButton, false},
        {ui->hetoorHealthLockPushButton, false},
        {ui->quadRangleNoCollisionPushButton, false}};

    updatePushButtonText();
}

void MainWindow::initPushButtonConnections()
{
    connect(ui->alternativeMenuUnlockPushButton, &QPushButton::clicked, this, &MainWindow::onAlternativeMenuUnlockPushButtonClicked);
    connect(ui->gameConsoleInvincibilityPushButton, &QPushButton::clicked, this, &MainWindow::onGameConsoleInvincibilityPushButtonClicked);
    connect(ui->dairyScandalInvincibilityAndInstantKillPushButton, &QPushButton::clicked, this, &MainWindow::onDairyScandalInvincibilityAndInstantKillPushButtonClicked);
    connect(ui->decreaseMitaSnowballsPushButton, &QPushButton::clicked, this, &MainWindow::onDecreaseMitaSnowballsPushButtonClicked);
    connect(ui->lockScoreOfMitaInDanceFloorPushButton, &QPushButton::clicked, this, &MainWindow::onLockScoreOfMitaInDanceFloorPushButtonClicked);
    connect(ui->spaceCarAlwaysFirstPlacePushButton, &QPushButton::clicked, this, &MainWindow::onSpaceCarAlwaysFirstPlacePushButtonClicked);
    connect(ui->spaceCarBossNeverHurtsYouPushButton, &QPushButton::clicked, this, &MainWindow::onSpaceCarBossNeverHurtsYouPushButtonClicked);
    connect(ui->hetoorHealthLockPushButton, &QPushButton::clicked, this, &MainWindow::onHetoorHealthLockPushButtonClicked);
    connect(ui->quadRangleNoCollisionPushButton, &QPushButton::clicked, this, &MainWindow::onQuadRangleNoCollisionPushButtonClicked);
}

void MainWindow::initLanguageAction()
{
    // 创建一个子菜单，用于语言切换
    QMenu *languageMenu = new QMenu(this);

    // 创建一个动作组，保证同一时间只有一个选中
    QActionGroup *langActionGroup = new QActionGroup(this);
    langActionGroup->setExclusive(true);

    // 支持的语言列表
    QList<QPair<QString, QString>> languages = {
        {"en_US", "English"},
        {"ru_RU", "Русский"},
        {"zh_CN", "简体中文"}};

    // 遍历创建菜单项
    for (const auto &lang : languages)
    {
        QAction *action = new QAction(lang.second, this);
        action->setCheckable(true);
        action->setData(lang.first); // 用data保存语言代码
        langActionGroup->addAction(action);
        languageMenu->addAction(action);

        // 如果当前系统语言等于此项，则默认勾选
        if (QLocale::system().name() == lang.first)
        {
            action->setChecked(true);
        }
    }

    // 连接动作组的信号，选择语言时进行处理
    connect(langActionGroup, &QActionGroup::triggered, this, [=](QAction *action)
            {
        QString selectedLang = action->data().toString();
        switchLanguage(selectedLang); });

    // 将子菜单设置给 actionLanguage
    ui->actionLanguage->setMenu(languageMenu);
}

void MainWindow::initAboutAction()
{
    WebsiteInfo githubInfo = {
        "https://github.com/favicon.ico",
        "CN-Scars",
        "https://github.com/CN-Scars/MisideTrainer",
        "https://github.com/CN-Scars"};

    WebsiteInfo nexusModsInfo = {
        "https://www.nexusmods.com/favicon.ico",
        "ScarsMusic",
        "https://www.nexusmods.com/miside/mods/339",
        "https://next.nexusmods.com/profile/ScarsMusic"};

    // 连接 "About" 菜单项的信号
    connect(ui->actionAbout_this_tool, &QAction::triggered, this, [=]()
            {
        // 创建对话框
        QDialog dialog(this);

        // 创建一个水平布局来包含每个网站的信息
        QHBoxLayout *mainLayout = new QHBoxLayout(&dialog);

        // GitHub 信息部分
        QVBoxLayout *githubLayout = new QVBoxLayout();
        createAboutInfoSection(&dialog, githubLayout, githubInfo);
        mainLayout->addLayout(githubLayout);

        // 添加一些间距
        mainLayout->addSpacing(10);

        // Nexus Mods 信息部分
        QVBoxLayout *nexusModsLayout = new QVBoxLayout();
        createAboutInfoSection(&dialog, nexusModsLayout, nexusModsInfo);
        mainLayout->addLayout(nexusModsLayout);

        // 显示对话框（模态）
        dialog.exec(); });
}

void MainWindow::initTextLabels()
{
    QHash<QLabel *, QString> labels = {
        {ui->processStatusLabel, "MiSideFull.exe %1"},
        {ui->moduleStatusLabel, "GameAssembly.dll %1"},
        {ui->alternativeMenuUnlockLabel, tr("100% unlock alternative menu")},
        {ui->gameConsoleInvincibilityLabel, tr("Game console invincible")},
        {ui->dairyScandalInvincibilityAndInstantKillLabel, tr("Dairy Scandal invincibility and instant kill")},
        {ui->decreaseMitaSnowballsLabel, tr("Decrease the number of Mita's snowballs")},
        {ui->lockScoreOfMitaInDanceFloorLabel, tr("Lock the score of Cap-wearing Mita in Dance Floor")},
        {ui->spaceCarAlwaysFirstPlaceLabel, tr("Space Car: Always first place")},
        {ui->spaceCarBossNeverHurtYouLabel, tr("Space Car: Boss never hurts you")},
        {ui->hetoorHealthLockLabel, tr("Hetoor health lock")},
        {ui->quadRangleNoCollisionLabel, tr("Quad Rangle: No collision")}};

    for (auto it = labels.begin(); it != labels.end(); ++it)
    {
        QLabel *label = it.key();
        QString text = it.value();
        // 如果text中有参数占位
        if (text.contains(".exe"))
        {
            QString loadStatus = processFound ? tr("found") : tr("not found");
            label->setText(text.arg(loadStatus));
        }
        else if (text.contains(".dll"))
        {
            QString loadStatus = moduleFound ? tr("found") : tr("not found");
            label->setText(text.arg(loadStatus));
        }
        else
        {
            label->setText(text);
        }

        label->setWordWrap(true);
    }
}

void MainWindow::switchLanguage(const QString &langCode)
{
    QString qmFile = QString(":/translations/MisideTrainer_%1.qm").arg(langCode);

    if (appTranslator)
    {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    appTranslator = new QTranslator(this);
    if (appTranslator->load(qmFile))
    {
        qApp->installTranslator(appTranslator);
    }

    // 更新当前界面文本
    ui->retranslateUi(this);
    // 手动更新其他文本
    initTextLabels();
    updatePushButtonText();
}

void MainWindow::handleProcessAndModuleStateChange()
{
    ui->processStatusLabel->setText(QString("MiSideFull.exe %1").arg(processFound ? tr("found") : tr("not found")));
    ui->moduleStatusLabel->setText(QString("GameAssembly.dll %1").arg(moduleFound ? tr("found") : tr("not found")));

    updatePictureLabel();

    if (!processFound or !moduleFound)
    {
        trainerManager->resetTrainers();
        resetPushButtonState();
    }
}

void MainWindow::updatePictureLabel()
{
    const QString picturePath = processFound && moduleFound ? ":/images/horror_mita_open_eyes.png" : ":/images/horror_mita_close_eyes.png";

    QPixmap horrorMitaPixmap(picturePath);
    QPixmap scaledPix = horrorMitaPixmap.scaled(ui->pictureLabel->size(),
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation);
    ui->pictureLabel->setPixmap(scaledPix);
}

void MainWindow::updatePushButtonText()
{
    for (auto it = pushButtonEnabled.begin(); it != pushButtonEnabled.end(); ++it)
    {
        QPushButton *pushButton = it.key();
        bool enabled = it.value();
        pushButton->setText(enabled ? tr("Disable") : tr("Enable"));
    }
}

void MainWindow::resetPushButtonState()
{
    std::for_each(pushButtonEnabled.begin(), pushButtonEnabled.end(), [](bool &value)
                  { value = false; });
    updatePushButtonText();
}

void MainWindow::createAboutInfoSection(QDialog *dialog, QVBoxLayout *sectionLayout, const WebsiteInfo &info)
{
    const QString &iconUrl = info.iconUrl;
    const QString &author = info.author;
    const QString &publishUrl = info.publishUrl;
    const QString &profileUrl = info.profileUrl;

    // 创建一个图标按钮，用于显示图标
    QPushButton *iconButton = new QPushButton(dialog);
    iconButton->setFlat(true); // 去掉边框
    connect(iconButton, &QPushButton::clicked, this, [=]()
            { QDesktopServices::openUrl(QUrl(publishUrl)); });
    sectionLayout->addWidget(iconButton, 0, Qt::AlignHCenter);

    // 使用 QNetworkAccessManager 异步下载图标图片
    QNetworkAccessManager *nam = new QNetworkAccessManager(iconButton);
    QNetworkRequest request((QUrl(iconUrl)));
    QNetworkReply *reply = nam->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, iconButton]()
            {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            if (pixmap.loadFromData(data))
            {
                iconButton->setIcon(QIcon(pixmap));
                iconButton->setIconSize(pixmap.size());
            }
        }
        reply->deleteLater(); });

    // 创建一个 QLabel 来显示作者信息，使用 HTML 超链接格式，点击超链接时会自动调用系统默认浏览器打开链接
    QLabel *label = new QLabel(dialog);
    label->setText(QString("<a href=\"%1\">%2</a>").arg(profileUrl, author));
    label->setAlignment(Qt::AlignHCenter);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
    sectionLayout->addWidget(label);
}
