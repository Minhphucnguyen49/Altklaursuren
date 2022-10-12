TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        farmingsimulator.cpp \
        main.cpp \
        orchard.cpp \
        owner.cpp \
        pasture.cpp \
        plot.cpp

HEADERS += \
    farmingsimulator.h \
    orchard.h \
    owner.h \
    pasture.h \
    plot.h
