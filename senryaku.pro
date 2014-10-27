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
    Application.hpp \
    Resources.hpp \
    controllers/playercontroller.hpp \
    events/category.hpp \
    events/command.hpp \
    events/commandqueue.hpp \
    resources/affectors.hpp \
    resources/animation.hpp \
    resources/musicplayer.hpp \
    resources/particle.hpp \
    resources/resourceholder.hpp \
    resources/resourceidentifiers.hpp \
    resources/scriptplayer.hpp \
    resources/soundplayer.hpp \
    states/state.hpp \
    states/stateidentifiers.hpp \
    states/statestack.hpp \
    states/titlestate.hpp \
    utils.hpp \
    States.hpp \
    Events.hpp \
    Controllers.hpp

