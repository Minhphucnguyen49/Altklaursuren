TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        customer.cpp \
        employee.cpp \
        fitnesscenter.cpp \
        main.cpp \
        person.cpp

HEADERS += \
    customer.h \
    employee.h \
    fitnesscenter.h \
    json.hpp \
    person.h
