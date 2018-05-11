#include "pawn.hpp"

Pawn::Pawn() {}

Color Pawn::getColor() const {
    return color_;
}

bool Pawn::isAlive() const {
    return isAlive_;
}

bool Pawn::isQueen() const {
    return isQueen_;
}

const Position &Pawn::getPosition() const {
    return position_;
}