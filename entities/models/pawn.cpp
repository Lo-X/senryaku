#include <entities/models/pawn.hpp>

Pawn::Pawn() :
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
    PawnPtr backup(new Pawn());
    backup->name = name;
    backup->type = type;
    backup->movements = movements;
    backup->hasPromotion = hasPromotion;
    backup->isPromoted = isPromoted;

    // Swap
    name = promotion->name;
    type = promotion->type;
    movements = promotion->movements;
    promotion = std::move(backup);
}
