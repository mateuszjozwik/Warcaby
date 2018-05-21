//
// Created by mateusz on 19.05.18.
//

#include "player.h"
#include <iostream>


Player::Player(int num) : num_(num) {
    std::cout << "PLAYER" << std::endl;
}

Player::~Player() {
    std::cout << "DESTROY_PLAYER" << std::endl;
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

