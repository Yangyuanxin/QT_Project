#-------------------------------------------------
#
# Project created by QtCreator 2019-03-23T17:47:18
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlite_test_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    record_info.h

FORMS    += mainwindow.ui
