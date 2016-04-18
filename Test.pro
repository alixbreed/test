#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T16:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editwindow.cpp \
    xmloperator.cpp

HEADERS  += mainwindow.h \
    editwindow.h \
    xmloperator.h \
    resources.rc

FORMS    += mainwindow.ui \
    editwindow.ui

RC_FILE     += \
    resources.rc
