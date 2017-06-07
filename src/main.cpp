#include <QTranslator>
#include <QDir>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(QDir::current().dirName() == "release")
        QDir::setCurrent("..");

    QTranslator translator;
    translator.load("sanguosha.qm");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
