INCLUDEPATH += ../corelib

HEADERS       = window.h \
                glWidget.h \
                Camera.h
SOURCES       = main.cpp \
                window.cpp \
                glWidget.cpp \
                Camera.cpp
QT           += opengl widgets


CONFIG += console
LIBS += -L"../corelib/debug" -lcorelib
# install
target.path = ../
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS executable.pro
sources.path = ../
INSTALLS += target sources
