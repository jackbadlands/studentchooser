#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T19:55:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = studentchooser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylistmodel.cpp

HEADERS  += mainwindow.h \
    mylistmodel.h \
    data.h

FORMS    += mainwindow.ui
