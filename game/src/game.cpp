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
    board_.setPawns(player_, enemy_);
    setCurrentMoveColor(Color::WHITE);
    setLastMoveColor(Color::BLACK);
}

Color Game::getLastMoveColor() {
    return lastMoveColor_;
}

Color Game::getCurrentMoveColor() {
    return currentMoveColor_;
}

void Game::setCurrentMoveColor(Color color) {
    currentMoveColor_ = color;
}

void Game::setLastMoveColor(Color color) {
    lastMoveColor_ = color;
}

void Game::restartGame() {
    board_.resetBoard(player_);
    board_.resetBoard(enemy_);
    board_.setPawns(player_, enemy_);
}

bool Game::canMove(int x, int y) {
    auto pawnField = make_shared<Field>(this->getBoard().getField(x, y));
    if (pawnField->getPawn().isQueen()) {
        bool checkNE = checkQueenDirection(pawnField, 1, -1);
        bool checkNW = checkQueenDirection(pawnField,-1, -1);
        bool checkSE = checkQueenDirection(pawnField, 1, +1);
        bool checkSW = checkQueenDirection(pawnField,-1, +1);

        cout << checkNE << " " << checkNW << " " << checkSE << " " << checkSW << endl;

        return (checkNE || checkNW || checkSE || checkSW);

    } else {
        bool checkNE = checkField(pawnField,  1, -1);
        bool checkNW = checkField(pawnField, -1, -1);
        bool checkSE = checkField(pawnField,  1, +1);
        bool checkSW = checkField(pawnField, -1, +1);

        cout << checkNE << " " << checkNW << " " << checkSE << " " << checkSW << endl;

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

bool Game::checkQueenDirection(PField pawnField, int x, int y) {
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

bool Game::canKill(PField pawnField, int x, int y) {
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

bool Game::canGoToField(PField pawnField, PField destinationField) {
//    todo: implement

    return false;
}

bool Game::fieldOnBoard(int x, int y) {
    return (x>-1 && x<8)
           && (y>-1 && y<8);
}

bool Game::fieldToKillOnBoard(int x, int y) {
    return (x>0 && x<7)
           && (y>0 && y<7);
}

bool Game::goingInValidDirection(PField pawnField, PField destinationField) {
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

bool Game::isQueenKilling(const PField pawnField, const PField destField) const {

    //coordinates of pawn which will be removed
    int from = pawnField->getX();
    int to = destField->getX();

    if (from > to) {
        for (int i=from+1 ; i<to ; i++) {
            if (this->getBoard().getField(i, i).hasPawn()) {
                return true;
            }
        }
        return false;
    } else {
        for (int i=to+1 ; i<from ; i++) {
            if (this->getBoard().getField(i, i).hasPawn()) {
                return true;
            }
        }
        return false;
    }
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
    removePawnByQueen(destX, destY, pawnX, pawnY);
}

bool Game::checkDirection(int yDiff, Color color) const {

    switch(color) {
        case Color::WHITE:
            return (yDiff>0);
        case Color::BLACK:
            return (yDiff<0);
    }
}

void Game::removePawnByQueen(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY) {

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
            cout << "CAN KILL: " << canKill << endl;
            return canKill;
        }
        case Color::BLACK: {
            bool canKill = enemy_.canPlayerKill();
            cout << "CAN KILL: " << canKill << endl;
            return canKill;
        }
    }
}