#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T15:55:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DebugMode
TEMPLATE = app


SOURCES += main.cpp\
    debugwindow.cpp \

HEADERS  += debugwindow.h \
    constants.h

FORMS    += debugwindow.ui

CONFIG += console
