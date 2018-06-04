//
// Created by mateusz on 19.05.18.
//

#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int num) : num_(num) {
}

Player::~Player() {
}

std::array<Pawn, 12>* Player::getPlayerPawns() {
    return &playerPawns_;
}

Pawn& Player::getPlayerPawn(int x, int y) {

    for (Pawn& pawn: playerPawns_) {
        if (pawn.getY() == y && pawn.getX() == x) {
            return pawn;
        }
    }
}

bool Player::canPlayerKill() const {
    for (const Pawn& pawn: playerPawns_) {
        if (pawn.isAlive() && pawn.checkIfPawnCanKill()) {
            return true;
        }
    }

    return false;
}