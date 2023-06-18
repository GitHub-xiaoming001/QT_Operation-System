#-------------------------------------------------
#
# Project created by QtCreator 2023-04-26T17:36:11
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = 1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        window.cpp \
    login.cpp \
    diannao.cpp \
    shijian.cpp \
    movie.cpp \
    txqq.cpp \
    weixin.cpp \
    game.cpp \
    gamewidget.cpp

HEADERS += \
        window.h \
    login.h \
    diannao.h \
    shijian.h \
    movie.h \
    txqq.h \
    weixin.h \
    game.h \
    gamewidget.h

FORMS += \
    window.ui \
    login.ui \
    movie.ui \
    diannao.ui \
    shijian.ui \
    movie.ui \
    txqq.ui \
    weixin.ui \
    game.ui \
    gamewidget.ui

RESOURCES += \
    pic.qrc \
    res.qrc
