#pragma once

#include <SFML/Graphics.hpp>

#include <states/state.hpp>
#include <network/networkprotocol.hpp>
#include <network/gameserver.hpp>

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

    virtual void        onDestroy();

private:
    void                handlePacket(sf::Int32 type, sf::Packet& packet);

private:
    sf::TcpSocket       mSocket;
    bool                mConnected;
    sf::Time            mTimeSinceLastPacket;
    sf::Clock           mPingClock;
};

