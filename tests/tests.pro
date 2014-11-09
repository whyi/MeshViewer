#-------------------------------------------------
#
# Project created by QtCreator 2013-06-29T22:01:00
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
INCLUDEPATH += ../corelib
LIBS += -L"../corelib/debug" -lcorelib
SOURCES += \
    CVecTests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
