#pragma once

#include <entities/models/pawn.hpp>

#include <SFML/Config.hpp>

#include <string>
#include <vector>

class Player
{
public:
    Player(sf::Uint32 id, const std::string& name, sf::Uint32 rank = 0);

public:
    sf::Uint32                  id;
    std::string                 name;
    sf::Uint32                  rank;
    std::vector<Pawn::PawnPtr>  reserve;
    // pawn theme
};

