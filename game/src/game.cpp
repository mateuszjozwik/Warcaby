#include "game.h"
#include "iostream"
#include <iostream>
#include "math.h"
Game::Game() {
    initGame();
}

Game& Game::getInstance() {
    static Game gameInstance;
    return gameInstance;
}

void const Game::initGame() {
    board_.setPawns(player_);
}

void Game::restartGame() {
    board_.resetBoard(player_);
    board_.setPawns(player_);
}

bool Game::canMove(int x, int y) {
    auto pawnField = make_shared<Field>(this->getBoard().getField(x, y));

    bool checkNE = checkField(pawnField, 1, -1);
    bool checkNW = checkField(pawnField, -1, -1);
    bool checkSE = checkField(pawnField, 1, +1);
    bool checkSW = checkField(pawnField, -1, +1);

    return (checkNE || checkNW || checkSE || checkSW);
}

bool Game::checkField(PField pawnField, int x, int y) {
    int pawnX = pawnField->getX();
    int pawnY = pawnField->getY();
    int fieldX = pawnX+x;
    int fieldY = pawnY+y;
    if (fieldOnBoard(fieldX, fieldY)) {
        auto destinationField = make_shared<Field>(this->getBoard().getField(fieldX, fieldY));
        bool hasPawn = destinationField->hasPawn();
        if (!hasPawn) {
            if (goingInValidDirection(pawnField, destinationField)) {
                return true;
            } else {
                return false;
            }
        } else {
            //Check if field next to current has pawn in different color
            if (destinationField->getPawn().getColor() != destinationField->getPawn().getColor()) {
                //check if next is on Board
                fieldX = fieldX+x;
                fieldY = fieldY+y;

                if (fieldOnBoard(fieldX, fieldY)) {
                    auto destinationField = make_shared<Field>(this->getBoard().getField(fieldX, fieldY));

                    return !destinationField->hasPawn();
                }
            }
        }
    }

    return false;
}

bool Game::fieldOnBoard(int x, int y) {
    return (x>-1 && x<8)
           && (y>-1 && y<8);
}

bool Game::goingInValidDirection(PField pawnField, PField destinationField) {
    //Fields which were in rows 0-2 at the beginning of game can only go to rows 3-7
    if (pawnField.get()->getPawn().getY()<3) {
        return (destinationField.get()->getY() > pawnField.get()->getY());
    } else {
        return (destinationField.get()->getY() < pawnField.get()->getY());
    }
}

const Board& Game::getBoard() const {
    return board_;
}

Board& Game::getBoardMutable() {
    return board_;
}

Player Game::getPlayer() const {
    return player_;
}

bool Game::validateMove(int destX, int destY, int pawnX, int pawnY) const {

    auto destinationField = make_shared<Field>(this->getBoard().getField(destX, destY));
    auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));

    if (destinationField->hasPawn()) {
        return false;
    } else {
        if (!pawnField->getPawn().isQueen()) {
            return validDistance(pawnField, destinationField);
        } else {
            return validQueenDistance(pawnField, destinationField);
        }
    }
}

bool Game::canRemove(int destX, int destY, int pawnX, int pawnY) const {

    int xDiff = destX - pawnX;
    int yDiff = destY - pawnY;

    int victimX = (pawnX + destX)/2;
    int victimY = (pawnY + destY)/2;
    if (abs(xDiff) == abs(yDiff) && abs(yDiff) == 2) {
        return this->getBoard().getField(victimX, victimY).hasPawn();
    }

    return false;
}

bool Game::isKilling(const PField pawnField, const PField destField) const {

    //coordinates of pawn which will be removed
    int victimX = (pawnField->getX() + destField->getX())/2;
    int victimY = (pawnField->getY() + destField->getY())/2;

    return this->getBoard().getField(victimX, victimY).hasPawn();
}

bool Game::validQueenDistance(const PField pawnField, const PField destField) const {
    return false;
}
bool Game::validDistance(const PField pawnField, const PField destField) const {

    int xDiff = destField.get()->getX() - pawnField.get()->getX();
    int yDiff = destField.get()->getY() - pawnField.get()->getY();

    bool isValidDirection = checkDirection(yDiff, pawnField.get()->getPawn().getColor());

    if (abs(xDiff) == abs(yDiff)) {
        switch (abs(xDiff)) {
            case 1:
                return isValidDirection;
            case 2:
                return isKilling(pawnField, destField);
            default:
                return false;
        }
    } else {
        return false;
    }
}

void Game::movePawn(int destX, int destY, int pawnX, int pawnY) {
    this->getBoardMutable().movePawn(destX, destY, pawnX, pawnY);
}

void Game::removePawn(int destX, int destY, int pawnX, int pawnY) {
    int victimX = (pawnX + destX)/2;
    int victimY = (pawnY + destY)/2;

    this->getBoardMutable().removePawn(victimX, victimY);
}

bool Game::checkDirection(int yDiff, Color color) const {

    switch(color) {
        case Color::WHITE:
            return (yDiff>0);
        case Color::BLACK:
            return (yDiff<0);
        default:
            return false;
    }
}
