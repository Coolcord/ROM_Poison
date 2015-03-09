#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T17:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROM_Poison
TEMPLATE = app


SOURCES += main.cpp\
        Main_Window.cpp \
    Corruptor_Settings.cpp

HEADERS  += Main_Window.h \
    Corruptor_Settings.h \
    Settings.h

FORMS    += Main_Window.ui \
    Corruptor_Settings.ui
