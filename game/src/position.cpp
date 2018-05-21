//
// Created by mateusz on 19.05.18.
//

#include "position.h"
Position::Position() {}
Position::Position(unsigned int x, unsigned int y) : x_(x), y_(y) {}

unsigned Position::getX() const {
    return x_;
}

unsigned Position::getY() const {
    return y_;
}

void Position::setPosition(unsigned int x, unsigned int y) {
    y_ = y;
    x_ = x;
}

bool operator ==(const Position &a, const Position &b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}

bool operator !=(const Position &a, const Position &b) {
    return !(a == b);
}
