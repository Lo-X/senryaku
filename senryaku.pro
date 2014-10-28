TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
QMAKE_CXXFLAGS += -std=c++11
OBJECTS_DIR = .obj
INCLUDEPATH += .

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
    events/commandqueue.cpp \
    entities/emitternode.cpp \
    entities/entity.cpp \
    entities/scenenode.cpp \
    entities/soundnode.cpp \
    entities/spritenode.cpp \
    entities/textnode.cpp \
    entities/particlenode.cpp \
    datatables.cpp \
    states/gamestate.cpp \
    network/gameserver.cpp

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
    Controllers.hpp \
    entities/emitternode.hpp \
    entities/entity.hpp \
    entities/scenenode.hpp \
    entities/soundnode.hpp \
    entities/spritenode.hpp \
    entities/textnode.hpp \
    Entities.hpp \
    entities/particlenode.hpp \
    datatables.hpp \
    states/gamestate.hpp \
    network/networkprotocol.hpp \
    network/gameserver.hpp

OTHER_FILES += \
    .travis.yml

