#ifndef BOARD_HPP
#define BOARD_HPP

#include <entities/models/pawn.hpp>

#include <map>
#include <set>

class Board
{
public:
    explicit Board(sf::Vector2u size);
    Board(unsigned int xSquareNb, unsigned int ySquareNb);

public:
    sf::Vector2u                            size;
    std::set<sf::Vector2u>                  promotionSquares;
    std::map<Pawn::PawnPtr, sf::Vector2u>   pawns;
};

#endif // BOARD_HPP
