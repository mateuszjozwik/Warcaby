#include "game.h"
#include "iostream"
#include <iostream>
#include "math.h"
Game::Game() {
}

Game& Game::getInstance() {
    static Game gameInstance;
    return gameInstance;
}

void const Game::initGame() {
    board_.setPawns(player_, enemy_);
    setLastMoveColor(Color::BLACK);
}

Color Game::getLastMoveColor() {
    return lastMoveColor_;
}

void Game::setLastMoveColor(Color color) {
    lastMoveColor_ = color;
}

void Game::restartGame() {
    board_.resetBoard(player_);
    board_.resetBoard(enemy_);
    board_.updateKills();
    board_.setPawns(player_, enemy_);
    setLastMoveColor(Color::BLACK);
}

bool Game::canMove(int x, int y) {
    auto pawnField = make_shared<Field>(this->getBoard().getField(x, y));
    if (pawnField->getPawn().isQueen()) {
        bool checkNE = checkQueenMove(pawnField, 1, -1);
        bool checkNW = checkQueenMove(pawnField,-1, -1);
        bool checkSE = checkQueenMove(pawnField, 1, +1);
        bool checkSW = checkQueenMove(pawnField,-1, +1);

        return (checkNE || checkNW || checkSE || checkSW);

    } else {
        bool checkNE = checkMove(pawnField,  1, -1);
        bool checkNW = checkMove(pawnField, -1, -1);
        bool checkSE = checkMove(pawnField,  1, +1);
        bool checkSW = checkMove(pawnField, -1, +1);

        return (checkNE || checkNW || checkSE || checkSW);
    }
}

bool Game::canPawnKill(int x, int y) {
    auto pawnField = make_shared<Field>(this->getBoard().getField(x, y));

    bool canKillNE = canKill(pawnField,  1, -1);
    bool canKillNW = canKill(pawnField, -1, -1);
    bool canKillSE = canKill(pawnField,  1, +1);
    bool canKillSW = canKill(pawnField, -1, +1);

    return (canKillNE || canKillNW || canKillSE || canKillSW);

}

bool Game::checkQueenMove(PField pawnField, int x, int y) {
    int pawnX = pawnField->getX();
    int pawnY = pawnField->getY();

    int fieldX = pawnX + x;
    int fieldY = pawnY + y;

    bool canMove = false;

    //Check if can move without killing
    while(fieldOnBoard(fieldX, fieldY)) {
        auto destinationField = make_shared<Field>(this->getBoard().getField(fieldX, fieldY));
        if (!destinationField.get()->hasPawn() && pawnsOnPath(pawnX, pawnY ,fieldX, fieldY) == 0) {
            canMove = true;
            break;
        }

        fieldX = fieldX + x;
        fieldY = fieldY + y;
    }

    //Check if queen can move with kill
    int fieldToGoX = pawnX + 2*x;
    int fieldToGoY = pawnY + 2*y;
    while(fieldOnBoard(fieldToGoX, fieldToGoY)) {
        if(pawnsOnPath(pawnX, pawnY, fieldToGoX, fieldToGoY, true) < 2) {
            canMove = true;
        }
        fieldToGoX = fieldToGoX + x;
        fieldToGoY = fieldToGoY + y;
    };

    return canMove;
}

int Game::pawnsOnPath(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY, bool countEnemies) const {

    int directionX = 1;
    if (fieldToGoX < pawnX) {
        directionX = -1;
    }

    int directionY = 1;
    if (fieldToGoY < pawnY) {
        directionY = -1;
    }

    int currentFieldX = pawnX+directionX;
    int currentFieldY = pawnY+directionY;

    int pawnsCount = 0;
    auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));
    auto fieldToGo = make_shared<Field>(this->getBoard().getField(fieldToGoX, fieldToGoY));

    while (currentFieldX != fieldToGoX && currentFieldY != fieldToGoY) {
        auto currentField = make_shared<Field>(this->getBoard().getField(currentFieldX, currentFieldY));

        if (countEnemies) {
            if (currentField->hasPawn()) {
                if (!fieldToGo->hasPawn() && currentField->getPawn().getColor() != pawnField->getPawn().getColor()) {
                    pawnsCount++;
                } else {
                    return 500;
                }
            }
        } else {
            if (currentField->hasPawn()) {
                pawnsCount++;
            }
        }

        currentFieldX += directionX;
        currentFieldY += directionY;
    }

    return pawnsCount;
}

bool Game::checkMove(PField pawnField, int x, int y) {
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
            if (pawnField->getPawn().getColor() != destinationField->getPawn().getColor()) {
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

bool Game::canKill(PField pawnField, int x, int y) const {
    int pawnX = pawnField->getX();
    int pawnY = pawnField->getY();
    int victimX = pawnX+x;
    int victimY = pawnY+y;
    int destinyX = victimX+x;
    int destinyY = victimY+y;

    if (fieldOnBoard(victimX, victimY) && fieldOnBoard(destinyX, destinyY)) {
        auto destinationField = make_shared<Field>(this->getBoard().getField(destinyX, destinyY));
        auto victimField = make_shared<Field>(this->getBoard().getField(victimX, victimY));
        auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));

        bool hasVictim = victimField->hasPawn();
        bool isOccupied = destinationField->hasPawn();

        if (!isOccupied && hasVictim) {
            return victimField->getPawn().getColor() != pawnField->getPawn().getColor();
        }
    }

    return false;
}

bool Game::fieldOnBoard(int x, int y) const {
    return (x>-1 && x<8)
           && (y>-1 && y<8);
}

bool Game::goingInValidDirection(const PField pawnField, const PField destinationField) const {
    //Fields which were in rows 0-2 at the beginning of game can only go to rows 3-7
    if (pawnField.get()->getPawn().getInitY()<3) {
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

bool Game::validateMove(int destX, int destY, int pawnX, int pawnY) const {

    auto destinationField = make_shared<Field>(this->getBoard().getField(destX, destY));
    auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));

    if (destinationField->hasPawn()) {
        return false;
    } else {
        if (!pawnField->getPawn().isQueen()) {
            return validDistance(pawnField, destinationField);
        } else if (abs(destX-pawnX) == abs(destY-pawnY)) {

            if (pawnsOnPath(pawnX, pawnY, destX, destY, true) < 2) {
                return true;
            }

            return false;
        }
    }
}

bool Game::canRemove(int destX, int destY, int pawnX, int pawnY) const {

    if (this->getBoard().getField(pawnX, pawnY).getPawn().isQueen()) {
        int pawns = pawnsOnPath(pawnX, pawnY, destX, destY, true);
        if (pawns == 1) {
            return true;
        }

        return false;
    }

    int xDiff = destX - pawnX;
    int yDiff = destY - pawnY;

    int victimX = (pawnX + destX)/2;
    int victimY = (pawnY + destY)/2;
    if (abs(xDiff) == abs(yDiff) && abs(yDiff) == 2) {

        return (this->getBoard().getField(victimX, victimY).getPawn().getColor()
                != this->getBoard().getField(pawnX, pawnY).getPawn().getColor());
    }

    return false;
}

bool Game::isKilling(const PField pawnField, const PField destField) const {

    //coordinates of pawn which will be removed
    int victimX = (pawnField->getX() + destField->getX())/2;
    int victimY = (pawnField->getY() + destField->getY())/2;

    if (this->getBoard().getField(victimX, victimY).hasPawn()) {
        return (this->getBoard().getField(victimX, victimY).getPawn().getColor() != pawnField.get()->getPawn().getColor());
    } else {
        return false;
    }
}

bool Game::validDistance(const PField pawnField, const PField destField) const {

    int xDiff = destField.get()->getX() - pawnField.get()->getX();
    int yDiff = destField.get()->getY() - pawnField.get()->getY();

    if (abs(xDiff) == abs(yDiff)) {
        switch (abs(xDiff)) {
            case 1:
                return goingInValidDirection(pawnField, destField);
            case 2:
                return isKilling(pawnField, destField);;
            default:
                return false;
        }
    } else {
        return false;
    }
}

void Game::movePawn(int destX, int destY, int pawnX, int pawnY) {
    auto destinationField = make_shared<Field>(this->getBoard().getField(destX, destY));
    auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));
    if (!destinationField->hasPawn() && pawnField->hasPawn()) {
        this->getBoardMutable().movePawn(destX, destY, pawnX, pawnY);
    }
}

void Game::removePawn(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY) {
    int directionX = 1;
    if (fieldToGoX < pawnX) {
        directionX = -1;
    }

    int directionY = 1;
    if (fieldToGoY < pawnY) {
        directionY = -1;
    }

    int currentFieldX = pawnX+directionX;
    int currentFieldY = pawnY+directionY;

    auto pawnField = make_shared<Field>(this->getBoard().getField(pawnX, pawnY));

    while (currentFieldX != fieldToGoX && currentFieldY != fieldToGoY) {
        auto currentField = make_shared<Field>(this->getBoard().getField(currentFieldX, currentFieldY));

        if (currentField->hasPawn()) {
            if (currentField->getPawn().getColor() != pawnField->getPawn().getColor()) {
                this->getBoardMutable().removePawn(currentFieldX, currentFieldY);
                break;
            }
        }

        currentFieldX += directionX;
        currentFieldY += directionY;
    }
}

bool Game::canPlayerKill(Color color) const {
    switch (color) {
        case Color::WHITE: {
            bool canKill = player_.canPlayerKill();
            return canKill;
        }
        case Color::BLACK: {
            bool canKill = enemy_.canPlayerKill();
            return canKill;
        }
    }
}