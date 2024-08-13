TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        expense.cpp \
        expensemanager.cpp \
        main.cpp \
        material.cpp \
        materialmanager.cpp

HEADERS += \
    expense.h \
    expensemanager.h \
    material.h \
    materialmanager.h
