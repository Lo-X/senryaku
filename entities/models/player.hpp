#pragma once

#include <SFML/Config.hpp>
#include <string>

class Player
{
public:
    Player(sf::Uint32 id, const std::string& name, sf::Uint32 rank = 0);

public:
    sf::Uint32          id;
    std::string         name;
    sf::Uint32          rank;
    // pawn theme
};

