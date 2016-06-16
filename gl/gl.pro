#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T13:29:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gl
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    objload.cpp \
    mainwindow.cpp \
    qextserialbase.cpp \
    win_qextserialport.cpp

HEADERS  += widget.h \
    objload.h \
    mainwindow.h \
    qextserialbase.h \
    win_qextserialport.h

FORMS    += widget.ui \
    mainwindow.ui
QT += opengl
