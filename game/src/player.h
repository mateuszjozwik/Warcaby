//
// Created by mateusz on 19.05.18.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "pawn.h"
#include "util.h"
#include "color.h"
#include "position.h"
#include <array>

class Player {
public:
    Player(int num = 0);
    ~Player();

    std::array<Pawn, 4>* getPlayerPawns();
    Pawn& getPlayerPawn(int x, int y);
    bool canPlayerKill() const;

    int num_;

private:
    std::array<Pawn, 4> playerPawns_;
    Pawn playerPawn_;
};


#endif //PLAYER_H
