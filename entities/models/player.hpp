#pragma once

#include <SFML/Config.hpp>
#include <string>

class Player
{
public:
    Player(const std::string& name, sf::Uint32 rank = 0);

public:
    std::string         name;
    sf::Uint32          rank;
    // pawn theme
};

