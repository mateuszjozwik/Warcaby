//
// Created by mateusz on 18.05.18.
//

#include <iostream>
#include "field.h"

Field::Field() { std::cout << "F";}
Field::Field(int xPos, int yPos, bool isGameField, bool hasPawn) :
        xPos_(xPos),
        yPos_(yPos),
        isGameField_(isGameField),
        hasPawn_(hasPawn) {}

//void Field::setPosition(int x, int y) {
//    position_.setPosition(x, y);
//}
//
//const Position& Field::getPosition() const {
//    return *position_;
//}

int Field::getX() {
    return xPos_;
}

int Field::getY() {
    return yPos_;
}

bool Field::hasPawn() const {
    return hasPawn_;
}

bool Field::setPawn(Pawn* pawn) {
    pawn_ = pawn;
}

bool Field::removePawn() {
}

Pawn& Field::getPawn() const {
    if (!pawn_) {
        throw std::invalid_argument("invalid pawn");
    }
    return *pawn_;
}

bool Field::isGameField() const {
    return isGameField_;
}

void Field::setX(int x) {
    xPos_ = x;
}

void Field::setY(int y) {
    yPos_ = y;
}

void Field::setIsGameField(bool isGameField) {
    isGameField_ = isGameField;
}

void Field::setHasPawn(bool hasPawn) {
    hasPawn_ = hasPawn;
}