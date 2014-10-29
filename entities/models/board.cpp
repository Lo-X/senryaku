#include <entities/models/board.hpp>
#include <algorithm>

Board::Board(sf::Vector2u size) :
    size(size)
{
}

Board::Board(unsigned int xSquareNb, unsigned int ySquareNb) :
    size(xSquareNb, ySquareNb)
{
}



void Board::eatPawn(sf::Vector2u position, Player &activePlayer)
{
    std::set<BoardPawn>::iterator it = std::find_if(pawns.begin(), pawns.end(), [&](const BoardPawn& bpwn)->bool {
        return bpwn.position == position;
    });

    if(it != pawns.end())
    {
        activePlayer.reserve.push_back(std::move((*it).pawn));
        pawns.erase(it);
    }
}
