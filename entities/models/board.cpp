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
    std::vector<BoardPawn>::iterator it = std::find_if(pawns.begin(), pawns.end(), [&](const BoardPawn& bpwn)->bool {
        return bpwn.position == position;
    });

    if(it != pawns.end())
    {
        (*it).pawn->demote();
        activePlayer.reserve.push_back(std::move((*it).pawn));
        pawns.erase(it);
    }
}

bool Board::canMovePawn(sf::Vector2u origin, sf::Vector2u destination)
{
    return canMove(origin, destination, false);
}

bool Board::movePawn(sf::Vector2u origin, sf::Vector2u destination)
{
    return canMove(origin, destination, true);
}



bool Board::canMove(sf::Vector2u origin, sf::Vector2u destination, bool doTheMove)
{
    // Is destination on the board ?
    if(destination.x >= size.x-1 || destination.y >= size.y)
        return false;

    std::vector<BoardPawn>::iterator it = std::find_if(pawns.begin(), pawns.end(), [&](const BoardPawn& bpwn)->bool {
        return bpwn.position == origin;
    });

    // Is there a pawn on the origin ?
    if(it != pawns.end())
    {
        for(sf::Vector2i& move : (*it).pawn->movements)
        {
            if(sf::Vector2u(origin.x+move.x, origin.y+move.y) == destination)
            {
                if(doTheMove)
                    (*it).position = destination;

                return true;
            }
        }
    }

    return false;
}
