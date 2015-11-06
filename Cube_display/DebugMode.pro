#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T15:55:38
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DebugMode
TEMPLATE = app


SOURCES += main.cpp\
    solver.cpp \
    fastsolver.cpp \
    modelprocessor.cpp \
    mainwindow.cpp \
    mytimer.cpp \
    appinterface.cpp \
    motorinterface.cpp

HEADERS  += \
    fastsolver.h \
    modelprocessor.h \
    constants.h \
    mainwindow.h \
    mytimer.h \
    appinterface.h \
    motorinterface.h

FORMS    += \
    mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
