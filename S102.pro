TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
include(MinGL2/mingl.pri)

SOURCES += \
        enemy.cpp \
        main.cpp \
        menu.cpp \
        player.cpp

HEADERS += \
    enemy.h \
    main.h \
    menu.h \
    player.h
