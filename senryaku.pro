TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -llua -ldl
QMAKE_CXXFLAGS += -std=c++11
OBJECTS_DIR = .obj

SOURCES += main.cpp \
    application/application.cpp

HEADERS += \
    application/application.hpp

