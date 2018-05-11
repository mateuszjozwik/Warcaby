#include "position.hpp"

Position::Position(unsigned int x, unsigned int y) : x_(x), y_(y) { }

unsigned Position::getX() const {
    return x_;
}

unsigned Position::getY() const {
    return y_;
}

bool operator ==(const Position &a, const Position &b) {
    return a.getX() == b.getX() &&
           a.getY() == b.getY();
}

bool operator !=(const Position &a, const Position &b) {
    return !(a == b);
}
