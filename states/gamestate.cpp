#include <states/gamestate.hpp>
#include <iostream>

//////////////////////////////////////////////////////////////////////

// TODO
// For now the local/internet mode is determined by ip.txt file,
// but we will need to make the difference in game via the main menu

#include <SFML/Network/IpAddress.hpp>
#include <fstream>

sf::IpAddress getAddressFromFile()
{
    {
        std::ifstream inputFile("ip.txt");
        std::string ipAddress;
        if (inputFile >> ipAddress)
            return ipAddress;
    }

    // If open/read failed, create new file
    std::ofstream outputFile("ip.txt");
    std::string localAddress = "127.0.0.1";
    outputFile << localAddress;
    return localAddress;
}

//////////////////////////////////////////////////////////////////////


GameState::GameState(StateStack &stack, Context context) :
    State(stack, context),
    mConnected(false)
{
    sf::IpAddress ip = getAddressFromFile();

    if(mSocket.connect(ip, ServerPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
    {
        mConnected = true;
    }
    else
    {
        std::cout << "Cannot connect to server " << ip.toString() << ":" << ServerPort << std::endl;
    }

    mSocket.setBlocking(false);
}


void GameState::draw()
{
}

bool GameState::update(sf::Time dt)
{
    if(!mConnected)
    {
        requestStackClear();
        return false;
    }

    // Get last recieved packets and check if we timed out
    sf::Packet packet;
    if (mSocket.receive(packet) == sf::Socket::Done)
    {
        mTimeSinceLastPacket = sf::seconds(0.f);
        sf::Int32 packetType;
        packet >> packetType;
        handlePacket(packetType, packet);
    }
    else if (mTimeSinceLastPacket > sf::seconds(5.f))
    {
        mConnected = false;
        std::cout << "Connection between client and server has been lost !" << std::endl;
        return false;
    }

    // Ping the server if needed to say we're still here
    if(mPingClock.getElapsedTime() >= sf::seconds(2.f))
    {
        sf::Packet packet;
        packet << static_cast<sf::Int32>(Client::Ping);
        mSocket.send(packet);
        mPingClock.restart();
    }


    // Incremen time since last packet recieved
    mTimeSinceLastPacket += dt;

    return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
    return true;
}


void GameState::onDestroy()
{
    if(mConnected)
    {
        sf::Packet packet;
        packet << static_cast<sf::Int32>(Client::Quit);
        mSocket.send(packet);
    }
}



void GameState::handlePacket(sf::Int32 type, sf::Packet &packet)
{
    switch(type)
    {
        // ...

        case Server::Pong:
            std::cout << "Server answered 'pong' !" << std::endl;
            break;

        default:
            break;
    }
}
