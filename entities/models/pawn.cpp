#include <entities/models/pawn.hpp>
#include <entities/models/player.hpp>

Pawn::Pawn(Player &owner) :
    owner(owner),
    name("Unamed Pawn"),
    type(PawnType::Unknown),
    hasPromotion(false),
    isPromoted(false),
    promotion(nullptr)
{
}



void Pawn::promote()
{
    if(hasPromotion && !isPromoted && promotion)
    {
        swapWithPromotion();
        isPromoted = true;
    }
}

void Pawn::demote()
{
    if(hasPromotion && isPromoted && promotion)
    {
        swapWithPromotion();
        isPromoted = false;
    }
}

void Pawn::swapWithPromotion()
{
    PawnPtr backup(new Pawn(owner));
    backup->name = name;
    backup->type = type;
    backup->owner = owner;
    backup->movements = movements;
    backup->hasPromotion = hasPromotion;
    backup->isPromoted = isPromoted;

    // Swap
    owner = promotion->owner;
    name = promotion->name;
    type = promotion->type;
    movements = promotion->movements;
    promotion = std::move(backup);
}
