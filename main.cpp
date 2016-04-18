﻿#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
