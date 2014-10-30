#pragma once

#include <entities/models/pawn.hpp>
#include <entities/models/player.hpp>

#include <map>
#include <vector>

class Board
{
public:
    struct BoardPawn
    {
        Pawn::PawnPtr   pawn;
        sf::Vector2u    position;
    };

public:
    explicit Board(sf::Vector2u size);
    Board(unsigned int xSquareNb, unsigned int ySquareNb);

    void            eatPawn(sf::Vector2u position, Player& activePlayer);

public:
    sf::Vector2u                            size;
    std::vector<sf::Vector2u>               promotionSquares;
    std::vector<BoardPawn>                  pawns;
};
