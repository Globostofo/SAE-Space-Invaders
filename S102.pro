TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
include(MinGL2/mingl.pri)

SOURCES += \
        box.cpp \
        button.cpp \
        entity.cpp \
        main.cpp \
        scene.cpp \
        spaceinvaders.cpp

HEADERS += \
    box.h \
    button.h \
    consts.h \
    entity.h \
    entity.h \
    scene.h \
    spaceinvaders.h
