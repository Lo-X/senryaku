#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>
#include <memory>

class Player;

class Pawn
{
public:
    enum PawnType
    {
        Unknown,
        King,
        Rook,
        Bishop,
        Squire,
        Knight, // Promotion of: Novice
    };

    typedef std::unique_ptr<Pawn> PawnPtr;

public:
    Pawn(Player& owner);

    void            promote();
    void            demote();

private:
    void            swapWithPromotion();

public:
    Player&                     owner;
    std::string                 name;
    PawnType                    type;
    std::vector<sf::Vector2i>   movements;
    bool                        hasPromotion;
    bool                        isPromoted;
    PawnPtr                     promotion;
};
