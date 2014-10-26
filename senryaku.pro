TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -llua -ldl
QMAKE_CXXFLAGS += -std=c++11
OBJECTS_DIR = .obj

SOURCES += main.cpp \
    application/application.cpp \
    utils.cpp \
    resources/affectors.cpp \
    resources/animation.cpp \
    resources/musicplayer.cpp \
    resources/particle.cpp \
    resources/soundplayer.cpp \
    states/state.cpp \
    states/statestack.cpp \
    states/titlestate.cpp \
    controllers/playercontroller.cpp \
    events/command.cpp \
    events/commandqueue.cpp

HEADERS += \
    application/application.hpp \
    utils.h \
    resources/affectors.h \
    resources/animation.h \
    resources/musicplayer.h \
    resources/particle.h \
    resources/resourceholder.h \
    resources/resourceidentifiers.h \
    resources/soundplayer.h \
    Application.hpp \
    Resources.hpp \
    states/state.h \
    states/stateidentifiers.h \
    states/statestack.h \
    states/titlestate.h \
    controllers/playercontroller.h \
    events/category.h \
    events/command.h \
    events/commandqueue.h \
    resources/scriptplayer.h

