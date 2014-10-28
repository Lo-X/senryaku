#include <network/gameserver.hpp>
#include <network/networkprotocol.hpp>

#include <iostream>

GameServer::RemotePeer::RemotePeer() :
    ready(false),
    timedOut(false)
{
    socket.setBlocking(false);
}

///////////////////////////////////////////////////////////////////


GameServer::GameServer() :
    mThread(&GameServer::executionThread, this),
    mWaitingThreadEnd(false),
    mTimeoutTime(sf::seconds(5.f)),
    mListeningState(false),
    mMaxConnectedPlayers(2),
    mConnectedPlayers(0),
    mPeers(1)
{
    mListenerSocket.setBlocking(false);
    mPeers[0].reset(new RemotePeer());
    //mThread.launch();
}

GameServer::~GameServer()
{
    mWaitingThreadEnd = true;
    mThread.wait();
}


void GameServer::run()
{
    executionThread();
}


void GameServer::setListening(bool enable)
{
    if(enable)
    {
        if(!mListeningState)
            mListeningState = (mListenerSocket.listen(ServerPort) == sf::TcpListener::Done);
    }
    else
    {
        mListenerSocket.close();
        mListeningState = false;
    }
}

void GameServer::executionThread()
{
    setListening(true);

    while(!mWaitingThreadEnd)
    {
        handleIncomingPackets();
        handleIncomingConnections();

        sf::sleep(sf::milliseconds(100));
    }
}


void GameServer::handleIncomingPackets()
{
    bool detectedTimeout = false;

    for(PeerPtr& peer : mPeers)
    {
        if(peer->ready)
        {
            sf::Packet packet;
            while(peer->socket.receive(packet) == sf::Socket::Done)
            {
                handleIncomingPacket(packet, *peer, detectedTimeout);

                peer->lastPacketTime = now();
                packet.clear();
            }

            if(now() >= (peer->lastPacketTime + mTimeoutTime))
            {
                peer->timedOut = true;
                detectedTimeout = true;
            }
        }
    }

    if(detectedTimeout)
        handleDisconnections();
}

void GameServer::handleIncomingPacket(sf::Packet &packet, RemotePeer &from, bool &detectedTimeOut)
{
    sf::Int32 packetType;
    packet >> packetType;

    std::cout << "[Server] Handling packet " << packetType << std::endl;

    switch(packetType)
    {
        case Client::Quit:
        case Client::Forfait:
            from.timedOut = true;
            detectedTimeOut = true;
            break;

        case Client::Ping:
        {
            sf::Packet packet;
            packet << static_cast<sf::Int32>(Server::Pong);
            from.socket.send(packet);
        } break;

            // ...

        default:
            std::cerr << "[Server] Unknown packet received of type " << packetType << std::endl;
            break;
    }
}

void GameServer::handleIncomingConnections()
{
    if(!mListeningState)
        return;

    if(mListenerSocket.accept(mPeers[mConnectedPlayers]->socket) == sf::TcpListener::Done)
    {
        // Set the new player info
        mPeers[mConnectedPlayers]->ready = true;
        mPeers[mConnectedPlayers]->lastPacketTime = now();

        mConnectedPlayers++;

        std::cout << "[Server] New client connected (#" << mConnectedPlayers << ") !" << std::endl;

        if(mConnectedPlayers >= mMaxConnectedPlayers)
            setListening(false);
        else
            mPeers.push_back(PeerPtr(new RemotePeer()));
    }
}

void GameServer::handleDisconnections()
{
    for(auto it = mPeers.begin(); it != mPeers.end(); )
    {
        if((*it)->timedOut)
        {
            std::cout << "[Server] A player has disconnected !" << std::endl;

            mConnectedPlayers--;
            it = mPeers.erase(it);

            if(mConnectedPlayers < mMaxConnectedPlayers)
            {
                mPeers.push_back(PeerPtr(new RemotePeer()));
                setListening(true);
            }
        }
        else
        {
            ++it;
        }
    }
}

void GameServer::sendToAll(sf::Packet &packet)
{
    for(PeerPtr& peer : mPeers)
    {
        if(peer->ready)
            peer->socket.send(packet);
    }
}

void GameServer::sendTo(RemotePeer &peer, sf::Packet &packet)
{
    if(peer.ready)
        peer.socket.send(packet);
}


sf::Time GameServer::now() const
{
    return mClock.getElapsedTime();
}
