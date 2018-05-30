//
// Created by mateusz on 18.05.18.
//

#include <iostream>
#include "pawn.h"

Pawn::Pawn(Color color, bool isAlive, bool isQueen, int x, int y)
        : color_(color),
          isAlive_(isAlive),
          isQueen_(isQueen),
          posx_(x),
          posy_(y){
    std::cout << "P ";
}

Pawn::~Pawn() {
    std::cout << "DP ";
}

Color Pawn::getColor() const {
    return color_;
}

void Pawn::setColor(Color color) {
    color_ = color;
}

bool Pawn::isAlive() const {
    return isAlive_;
}

bool Pawn::isQueen() const {
    return isQueen_;
}

void Pawn::promoteToQueen() {
    isQueen_ = true;
}

void Pawn::kill() {
    isAlive_ = false;
}

void Pawn::setX(int x) {
    posx_ = x;
}

void Pawn::setY(int y) {
    posy_ = y;
}

int Pawn::getX() {
    return posx_;
}

int Pawn::getY() {
    return posy_;
}

void Pawn::setQueen(bool isQueen) {
    isQueen_ = isQueen;
}