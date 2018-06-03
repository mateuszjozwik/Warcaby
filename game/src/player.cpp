//
// Created by mateusz on 19.05.18.
//

#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int num) : num_(num) {
    std::cout << "PLAYER" << std::endl;
}

Player::~Player() {
    std::cout << "DESTROY_PLAYER" << std::endl;
}

std::array<Pawn, 4>* Player::getPlayerPawns() {
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
            cout << "X: " << pawn.getX() << " Y: " << pawn.getY() << " Is alive: " << pawn.isAlive() << " Can Kill: " << pawn.checkIfPawnCanKill() << endl;

            return true;
        }
    }

    return false;
}