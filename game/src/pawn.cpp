//
// Created by mateusz on 18.05.18.
//

#include <iostream>
#include "pawn.h"
#include "game.h"

Pawn::Pawn(Color color, bool isAlive, bool isQueen, int x, int y, bool justKilled)
        : color_(color),
          isAlive_(isAlive),
          isQueen_(isQueen),
          posx_(x),
          posy_(y),
          justKilled_(justKilled){
}

Pawn::~Pawn() {
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

int Pawn::getX() const {
    return posx_;
}

int Pawn::getY() const {
    return posy_;
}

void Pawn::initY(int y) {
    initPosy_ = y;
}

int Pawn::getInitY() {
    return initPosy_;
}

bool Pawn::justKilled() {
    return justKilled_;
}

void Pawn::setJustKilled(bool justKilled) {
    justKilled_ = justKilled;
}

void Pawn::setQueen(bool isQueen) {
    isQueen_ = isQueen;
}

bool Pawn::checkIfPawnCanKill() const {

    bool canKillNE = canKillInDirection( 1, -1);
    bool canKillNW = canKillInDirection(-1, -1);
    bool canKillSE = canKillInDirection( 1, +1);
    bool canKillSW = canKillInDirection(-1, +1);

    return (canKillNE || canKillNW || canKillSE || canKillSW);
}

bool Pawn::canKillInDirection(int x, int y) const {

    int pawnX = getX();
    int pawnY = getY();

    if (isQueen()) {
        //Check if queen can move with kill
        int fieldToGoX = pawnX + 2*x;
        int fieldToGoY = pawnY + 2*y;
        while(Game::getInstance().fieldOnBoard(fieldToGoX, fieldToGoY)) {
            if(Game::getInstance().pawnsOnPath(pawnX, pawnY, fieldToGoX, fieldToGoY, true) == 1) {
                return true;
            }
            fieldToGoX = fieldToGoX + x;
            fieldToGoY = fieldToGoY + y;
        };

        return false;
    } else {
        int victimX = pawnX+x;
        int victimY = pawnY+y;
        int destinyX = victimX+x;
        int destinyY = victimY+y;

        if (Game::getInstance().fieldOnBoard(victimX, victimY) && Game::getInstance().fieldOnBoard(destinyX, destinyY)) {

            auto destinationField = make_shared<Field>(Game::getInstance().getBoard().getField(destinyX, destinyY));
            auto victimField = make_shared<Field>(Game::getInstance().getBoard().getField(victimX, victimY));

            bool hasVictim = victimField->hasPawn();
            bool isOccupied = destinationField->hasPawn();

            if (!isOccupied && hasVictim) {
                return victimField->getPawn().getColor() != getColor();
            }
        }

        return false;
    }
}
