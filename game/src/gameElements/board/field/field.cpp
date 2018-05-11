#include "field.hpp"

Field::Field(const Position &position) {}


const Pawn& Field::getPawn() const {
    return *pawn_;
}

const Position& Field::getPosition() const {
    return position_;
}

bool Field::hasPawn() const {
    return pawn_!= nullptr;
}

//void Field::removePawn() {
//
//}

//void Field::addPawn(const Pawn &pawn) {}
//