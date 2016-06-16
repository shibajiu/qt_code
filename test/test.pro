#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T11:44:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qextserialbase.cpp \
    win_qextserialport.cpp

HEADERS  += mainwindow.h \
    qextserialbase.h \
    win_qextserialport.h

FORMS    += mainwindow.ui

DISTFILES +=
