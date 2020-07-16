#-------------------------------------------------
#
# Project created by QtCreator 2020-07-13T09:59:32
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HShell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    connectdialog.cpp \
    serialport.cpp \
    configdialog.cpp \
    serialform.cpp \
    filetool.cpp \
    configtool.cpp

HEADERS  += mainwindow.h \
    console.h \
    connectdialog.h \
    serialport.h \
    configdialog.h \
    serialform.h \
    config.h \
    baseport.h \
    filetool.h

FORMS    += mainwindow.ui \
    connectdialog.ui \
    configdialog.ui \
    serialform.ui

RESOURCES += \
    images.qrc
