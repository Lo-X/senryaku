#include <bandit/bandit.h>
#include <entities/models/board.hpp>
#include <entities/models/pawn.hpp>
#include <entities/models/player.hpp>

using namespace bandit;


go_bandit([]() {
    // This set of tests are meant to be sure our base game class hold
    // the data and behave correctly.

    sf::Uint32  id =    42;
    std::string name =  "SuperPlayer";
    sf::Uint32  rank =  1;
    Player superplayer(id, name, rank);

    Pawn::PawnPtr knight(new Pawn(superplayer));
    knight->name            = "Knight";
    knight->type            = Pawn::Knight;
    knight->movements.push_back(sf::Vector2i(0, 1));
    knight->movements.push_back(sf::Vector2i(0, -1));
    knight->movements.push_back(sf::Vector2i(1, 0));
    knight->movements.push_back(sf::Vector2i(-1, 0));

    Pawn::PawnPtr squire(new Pawn(superplayer));
    squire->name            = "Squire";
    squire->type            = Pawn::Squire;
    squire->hasPromotion    = true;
    squire->promotion       = knight;
    squire->movements.push_back(sf::Vector2i(0, 1));

    Board board(3, 4);
    board.promotionSquares.push_back(sf::Vector2u(0, 0));
    board.promotionSquares.push_back(sf::Vector2u(1, 1));
    board.promotionSquares.push_back(sf::Vector2u(2, 2));
    board.promotionSquares.push_back(sf::Vector2u(3, 0));
    board.promotionSquares.push_back(sf::Vector2u(3, 1));
    board.promotionSquares.push_back(sf::Vector2u(3, 2));

    // Test the Player class
    describe("A Player", [&]() {

        it("attributes should match Player contructor's arguments", [&]() {
            AssertThat(superplayer.id, Equals(id));
            AssertThat(superplayer.name, Equals(name));
            AssertThat(superplayer.rank, Equals(rank));
        });

        it("should have an empty reserve at initialisation", [&]() {
            AssertThat(superplayer.reserve.empty(), Equals(true));
        });

    });


    // Test the Pawn class
    describe("A Pawn", [&]() {

        Pawn::PawnPtr lambda(new Pawn(superplayer));

        it("should have right default values at construction", [&]() {
            AssertThat(lambda->type, Equals(Pawn::Unknown));
            AssertThat(lambda->hasPromotion, Equals(false));
            AssertThat(lambda->isPromoted, Equals(false));
            AssertThat(lambda->movements.empty(), Equals(true));
        });

        it("without promotion shouldn't be promoted", [&]() {
            lambda->promote();
            AssertThat(lambda->isPromoted, Equals(false));
        });

        lambda = squire;

        it("with promotion should be promoted", [&]() {
            std::string     squire_name             = lambda->name;
            Pawn::PawnType  squire_type             = lambda->type;
            std::size_t     squire_movement_count   = lambda->movements.size();

            lambda->promote();

            AssertThat(lambda->isPromoted, Equals(true));
            AssertThat(lambda->hasPromotion, Equals(true)); // We still need to know that there is a promotion to demote()
            AssertThat(lambda->name, !Equals(squire_name));
            AssertThat(lambda->name, Equals(knight->name));
            AssertThat(lambda->type, !Equals(squire_type));
            AssertThat(lambda->type, Equals(knight->type));
            AssertThat(lambda->movements.size(), IsGreaterThan(squire_movement_count));
            AssertThat(lambda->movements, Equals(knight->movements));
        });

        it("cannot be promoted twice", [&]() {
            lambda->promote();

            AssertThat(lambda->isPromoted, Equals(true));
            AssertThat(lambda->hasPromotion, Equals(true)); // We still need to know that there is a promotion to demote()
            AssertThat(lambda->name, Equals(knight->name));
            AssertThat(lambda->type, Equals(knight->type));
            AssertThat(lambda->movements, Equals(knight->movements));
        });

        it("promoted should be demoted", [&]() {
            std::string     knight_name             = lambda->name;
            Pawn::PawnType  knight_type             = lambda->type;
            std::size_t     knight_movement_count   = lambda->movements.size();

            lambda->demote();

            AssertThat(lambda->isPromoted, Equals(false));
            AssertThat(lambda->hasPromotion, Equals(true));
            AssertThat(lambda->name, !Equals(knight_name));
            AssertThat(lambda->name, Equals(squire->name));
            AssertThat(lambda->type, !Equals(knight_type));
            AssertThat(lambda->type, Equals(squire->type));
            AssertThat(lambda->movements.size(), IsLessThan(knight_movement_count));
            AssertThat(lambda->movements, Equals(squire->movements));
        });

        it("can be promoted again after demotion", [&]() {
            std::string     squire_name             = lambda->name;
            Pawn::PawnType  squire_type             = lambda->type;
            std::size_t     squire_movement_count   = lambda->movements.size();

            lambda->promote();

            AssertThat(lambda->isPromoted, Equals(true));
            AssertThat(lambda->hasPromotion, Equals(true)); // We still need to know that there is a promotion to demote()
            AssertThat(lambda->name, !Equals(squire_name));
            AssertThat(lambda->name, Equals(knight->name));
            AssertThat(lambda->type, !Equals(squire_type));
            AssertThat(lambda->type, Equals(knight->type));
            AssertThat(lambda->movements.size(), IsGreaterThan(squire_movement_count));
            AssertThat(lambda->movements, Equals(knight->movements));
        });

    });


    // Test the Board class
    describe("A Board", [&]() {

        sf::Vector2u pawn_position(1,2);
        sf::Vector2u empty_position(2,3);

        it("is empty at creation", [&]() {
            AssertThat(board.pawns.empty(), Equals(true));
        });

        board.pawns.push_back({squire, pawn_position});

        it("should have one pawn on board", [&]() {
            AssertThat(board.pawns.size(), Equals(1));

            // Eat on an empty square (shouldn't do anything)
            board.eatPawn(empty_position, superplayer);

            AssertThat(board.pawns.size(), Equals(1));
        });

        it("should be empty again after the pawn has been eaten by a player", [&]() {
            board.eatPawn(pawn_position, superplayer);

            AssertThat(board.pawns.size(), Equals(0));
            AssertThat(superplayer.reserve.size(), Equals(1));
        });

    });


    // Test eaten pawns on Board and Player reserve
    // Test the Board class
    describe("an eaten Pawn", [&]() {

        sf::Vector2u pawn_position(1,2);
        sf::Vector2u empty_position(2,3);

        superplayer.reserve.clear();
        board.pawns.clear();
        board.pawns.push_back({squire, pawn_position});

        Pawn::PawnType squire_type = squire->type;
        squire->promote(); // becomes a Pawn::Knight

        it("should be demoted when eaten", [&]() {
            AssertThat(squire->type, !Equals(squire_type));

            board.eatPawn(pawn_position, superplayer);

            AssertThat(squire->type, Equals(squire_type));
            AssertThat(superplayer.reserve.size(), Equals(1));
        });

    });

});
