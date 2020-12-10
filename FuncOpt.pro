TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Area.cpp \
        FuncOpt.cpp \
        OptMethod.cpp \
        StopCriterion.cpp \
        main.cpp

HEADERS += \
    area.h \
    funcOpt.h \
    optmethod.h \
    stopCrit.h
