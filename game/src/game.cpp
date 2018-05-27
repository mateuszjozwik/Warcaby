#include "game.h"
#include "iostream"
#include <iostream>
#include "math.h"
Game::Game() {
    std::cout << "createGame" << std::endl;
    initGame();
}

Game& Game::getInstance() {
    std::cout << "getGameInstance" << std::endl;
    static Game gameInstance;
    return gameInstance;
}

void const Game::initGame() {
    std::cout << "initGame()" << std::endl;
    board_.setPawns(player_);
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

bool Game::validQueenDistance(const PField pawnField, const PField destField) const {

}
bool Game::validDistance(const PField pawnField, const PField destField) const {

    int xDiff = pawnField.get()->getX() - destField.get()->getX();
    int yDiff = pawnField.get()->getY() - destField.get()->getY();

    if (abs(xDiff) == abs(yDiff) && abs(xDiff) == 1 && abs(yDiff) == 1) {
        return true;
    }

    return false;
}

void Game::movePawn(int destX, int destY, int pawnX, int pawnY) {
    this->getBoardMutable().movePawn(destX, destY, pawnX, pawnY);
}