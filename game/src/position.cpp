//
// Created by mateusz on 19.05.18.
//

#include "position.h"
Position::Position(unsigned int x, unsigned int y) : x_(x), y_(y) {}

unsigned Position::getX() const {
    return x_;
}

unsigned Position::getY() const {
    return y_;
}