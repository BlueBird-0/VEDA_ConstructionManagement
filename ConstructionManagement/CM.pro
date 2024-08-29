TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        client.cpp \
        clientmanager.cpp \
        employee.cpp \
        employeemanager.cpp \
        expense.cpp \
        expensemanager.cpp \
        main.cpp \
        manager.cpp \
        material.cpp \
        materialmanager.cpp \
        project.cpp \
        projectmanager.cpp

HEADERS += \
    Object.h \
    client.h \
    clientmanager.h \
    employee.h \
    employeemanager.h \
    expense.h \
    expensemanager.h \
    manager.h \
    material.h \
    materialmanager.h \
    project.h \
    projectmanager.h
