#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T21:09:38
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoBang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboard.cpp \
    adddialog.cpp \
    linkdialog.cpp

HEADERS  += mainwindow.h \
    chessboard.h \
    adddialog.h \
    linkdialog.h

FORMS    += mainwindow.ui \
    adddialog.ui \
    linkdialog.ui
