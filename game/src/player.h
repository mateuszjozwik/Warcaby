//
// Created by mateusz on 19.05.18.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "pawn.h"
#include "util.h"
#include "color.h"
#include <array>

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

class GAME_STATE_DLL( Player ) {
public:
    Player(int num = 0);
    ~Player();

    std::array<Pawn, 12>* getPlayerPawns();
    Pawn& getPlayerPawn(int x, int y);
    bool canPlayerKill() const;

    int num_;

private:
    std::array<Pawn, 12> playerPawns_;
    Pawn playerPawn_;
};


#endif //PLAYER_H
