//
// Created by mateusz on 18.05.18.
//

#include <iostream>
#include "field.h"

Field::Field() {};

Field::Field(int xPos, int yPos, bool isGameField, bool hasPawn) :
        xPos_(xPos),
        yPos_(yPos),
        isGameField_(isGameField),
        hasPawn_(hasPawn) {}

int Field::getX() {
    return xPos_;
}

int Field::getY() {
    return yPos_;
}

int Field::getXConst() const {
    return xPos_;
}

int Field::getYConst() const {
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
        throw std::invalid_argument("Invalid pawn exception");
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