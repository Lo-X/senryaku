#include <entities/models/board.hpp>

Board::Board(sf::Vector2u size) :
    size(size)
{
}

Board::Board(unsigned int xSquareNb, unsigned int ySquareNb) :
    size(xSquareNb, ySquareNb)
{
}
