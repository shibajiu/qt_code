#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T11:56:29
#
#-------------------------------------------------

QT       -= gui

TARGET = ObjLoad
TEMPLATE = lib

DEFINES += OBJLOAD_LIBRARY

SOURCES += objload.cpp

HEADERS += objload.h\
        objload_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
