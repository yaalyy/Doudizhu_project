QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardpicture.cpp \
    gameprocess.cpp \
    hand.cpp \
    index.cpp \
    main.cpp \
    maininterface.cpp \
    method.cpp \
    player.cpp \
    robot.cpp \
    structures.cpp \
    userplayer.cpp

HEADERS += \
    card.h \
    cardpicture.h \
    functions.h \
    gameprocess.h \
    hand.h \
    index.h \
    maininterface.h \
    method.h \
    player.h \
    robot.h \
    structures.h \
    userplayer.h

FORMS += \
    index.ui \
    maininterface.ui

TRANSLATIONS += \
    Doudizhu_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/bk.png
