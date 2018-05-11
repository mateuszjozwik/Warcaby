#ifndef FIELD_HPP
#define FIELD_HPP

#include "../../pawn/pawn.hpp"
#include "../../../position.hpp"

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
class GAME_STATE_DLL( Field ) {

    /// coordinates of field on board
    Position position_;

//    /// pawn placed on the field
    const Pawn* pawn_ = nullptr;

public:
    Field(const Position &position = {});

    const Position& getPosition() const;
    const Pawn& getPawn() const;
    bool hasPawn() const;
//
//    void removePawn();
//
//    void addPawn(const Pawn &pawn);
};


#endif //FIELD_HPP
