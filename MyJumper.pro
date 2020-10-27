#-------------------------------------------------
#
# Project created by QtCreator 2020-07-28T20:48:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyJumper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QT += multimedia
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        button.cpp \
        cactus.cpp \
        coin.cpp \
        gamescene.cpp \
        gamesettings.cpp \
        gametext.cpp \
        ground.cpp \
        main.cpp \
        mainscene.cpp \
        menuscene.cpp \
        optionsscene.cpp \
        player.cpp \
        sky.cpp \
        view.cpp

HEADERS += \
        button.h \
        cactus.h \
        coin.h \
        gamescene.h \
        gamesettings.h \
        gametext.h \
        ground.h \
        mainscene.h \
        menuscene.h \
        optionsscene.h \
        player.h \
        sky.h \
        view.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
