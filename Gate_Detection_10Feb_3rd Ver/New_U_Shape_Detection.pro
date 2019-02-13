#-------------------------------------------------
#
# Project created by QtCreator 2018-11-17T20:21:18
#
#-------------------------------------------------
QT       += core

QT       -= gui
QT += widgets
TARGET = New_U_Shape_Detection
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    handler.cpp \
    colordetection.cpp \
    udetection.cpp \
    videocap.cpp

HEADERS += \
    handler.h \
    colordetection.h \
    udetection.h \
    videocap.h

LIBS += `pkg-config opencv --libs`
INCLUDEPATH += /usr/local/include/opencv
