TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp

LIBS += $$OUT_PWD/../ann/debug/libann.a
INCLUDEPATH += $$PWD/../ann/src
