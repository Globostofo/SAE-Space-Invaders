TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
include(MinGL2/mingl.pri)

SOURCES += \
        box.cpp \
        entity.cpp \
        main.cpp \
        menu.cpp \
        spaceinvaders.cpp

HEADERS += \
    box.h \
    consts.h \
    entity.h \
    entity.h \
    menu.h \
    spaceinvaders.h
