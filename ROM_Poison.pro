#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T17:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROM_Poison
TEMPLATE = app
CONFIG += c++11 pendantic Wall


SOURCES += main.cpp\
        Main_Window.cpp \
    Corruptor_Settings.cpp \
    Settings_Profile_Manager.cpp

HEADERS  += Main_Window.h \
    Corruptor_Settings.h \
    Settings.h \
    Settings_Profile_Manager.h

FORMS    += Main_Window.ui \
    Corruptor_Settings.ui

RC_FILE = ROM_Corruptor.rc

DISTFILES +=
