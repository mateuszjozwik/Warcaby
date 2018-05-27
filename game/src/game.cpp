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

bool Game::canMove(int x, int y) const {
    auto pawnField = make_shared<Field>(this->getBoard().getField(x, y));

    return true;
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
    }
}
