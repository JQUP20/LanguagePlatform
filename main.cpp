#include "mainwindow.h"

#include <QFile>
#include <QSettings>
#include <QApplication>
#include <QDebug>

#include "global.h"

#include "public/include/iconhelper.h"
#include "datamgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setFont(QFont("Microsoft Yahei", 10));
    a.setWindowIcon(QIcon(":/img/img/icon.png"));

    MainWindow w;

    QDEBUG() << "BEGIN";
    QFile file_dark(":/qdarkstyle/style.qss");

//    QSettings settings(SETTINGSFILE, QSettings::IniFormat);
//    bool useDark = settings.value("darkModeCheck", true).toBool();

//    if (file_dark.open(QFile::ReadOnly)) {
//        QString StyleSheet = QLatin1String(file_dark.readAll());
//        a.setStyleSheet(StyleSheet);
//        file_dark.close();
//    }

//    a.setFont(QFont("Microsoft Yahei", 10));
//    a.setWindowIcon(QIcon(":/img/img/icon.png"));


    QApplication::setQuitOnLastWindowClosed(false);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QFile file(":/css/css/youdao.css");
    if (file.open(QFile::ReadOnly))
    {
        qDebug() << "end121" << endl;
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    DATAMGR->Open();
    qDebug() << "start" << endl;

    IconHelper::Load();
    w.show();
    QDEBUG() << "END";
    return a.exec();
}
