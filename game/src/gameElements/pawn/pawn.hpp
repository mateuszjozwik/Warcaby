#ifndef PAWN_HPP
#define PAWN_HPP

#include "../../color.hpp"
#include "../../position.hpp"

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//msvc disable warnings for sheduler_ and history_ member
#pragma warning(disable:4251)
#endif


#ifdef GAME_STATE_EXPORTS
/** Workaround for Windows DLL library exports */
#define GAME_STATE_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define GAME_STATE_DLL(X) X
#endif

/**
   game state representation
*/
class GAME_STATE_DLL( Pawn ) {

    Position position_;
    /// [Color::WHITE, Color::BLACK]
    Color color_;
    bool isAlive_;
    bool isQueen_;

public:
    Pawn();
//    Pawn(const Pawn&) = default;
//    Pawn& operator =(const Pawn&) = default;

    bool isAlive() const;
    bool isQueen() const;
    Color getColor() const;
    const Position& getPosition() const;
};


#endif //PAWN_HPP
