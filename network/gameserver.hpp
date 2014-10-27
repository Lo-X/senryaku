#pragma once

#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <vector>
#include <memory>

class GameServer
{
public:
    GameServer();
    ~GameServer();

    // TODO : remove
    void    run();

private:
    struct RemotePeer
    {
        RemotePeer();

        sf::TcpSocket   socket;
        bool            ready;
        bool            timedOut;

        sf::Time        playedTime;
        sf::Time        roundTime;
        sf::Time        lastPacketTime;
    };

    typedef std::unique_ptr<RemotePeer> PeerPtr;

private:
    void            setListening(bool enable);
    void            executionThread();

    void            handleIncomingPackets();
    void            handleIncomingPacket(sf::Packet& packet, RemotePeer& from, bool& detectedTimeOut);

    void            handleIncomingConnections();
    void            handleDisconnections();

    void            sendToAll(sf::Packet& packet);
    void            sendTo(RemotePeer& peer, sf::Packet& packet);

    sf::Time        now() const;

private:
    sf::Thread              mThread;
    bool                    mWaitingThreadEnd;
    sf::Clock               mClock;
    sf::Time                mTimeoutTime;
    sf::TcpListener         mListenerSocket;
    bool                    mListeningState;

    std::size_t             mMaxConnectedPlayers;
    std::size_t             mConnectedPlayers;

    std::vector<PeerPtr>    mPeers;
};
