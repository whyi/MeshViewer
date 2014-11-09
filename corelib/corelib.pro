INCLUDEPATH += 

TEMPLATE = lib
CONFIG += staticlib
HEADERS  = CMesh.h \
           CVec.h \
           Log.h
SOURCES = CMesh.cpp \
          CVec.cpp
QT           += opengl

# install
target.path = .
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS corelib.pro
sources.path = .
INSTALLS += target sources
