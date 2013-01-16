#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T07:36:36
#
#-------------------------------------------------

QT       += core xml network dbus

QT       -= gui

TARGET = tori-daemon
CONFIG += console 
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/release/ -ltori-daemon-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/debug/ -ltori-daemon-lib
else:unix: LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib
