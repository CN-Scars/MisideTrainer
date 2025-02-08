#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 根据用户语言环境设置翻译文件
    QTranslator translator;
    QString locale = QLocale::system().name();
    QString loadFileName;
    QList<QString> supportLangs = {"en_US", "ru_RU", "zh_CN"};
    if (supportLangs.contains(locale))
    {
        loadFileName = QString(":/translations/MisideTrainer_%1.qm").arg(locale);
        if (translator.load(loadFileName))
        {
            a.installTranslator(&translator);
        }
    }

    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/app_icon.ico"));
    w.setFixedSize(400, 600);
    w.setWindowTitle("MisideFull Trainer");
    w.show();
    return a.exec();
}
