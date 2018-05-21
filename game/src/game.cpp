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

    auto field = make_shared<Field>(this->getBoard().getField(destX, destY));
    auto pawn = make_shared<Pawn>(this->getPlayer().getPlayerPawn(pawnX, pawnY));


    if (field->hasPawn()) {
        return false;
    } else {
        bool isValid;
        if (!pawn->isQueen()) {
            return validDistance(pawn, field);
        } else {
            return validQueenDistance(pawn, field);
        }
    }
}

bool Game::validQueenDistance(const PPawn pawn, const PField destField) const {

}
bool Game::validDistance(const PPawn pawn, const PField destField) const {

    int xDiff = pawn.get()->getX() - destField.get()->getX();
    int yDiff = pawn.get()->getY() - destField.get()->getY();

    if (xDiff == yDiff && abs(xDiff) == 1) {
        return true;
    }

}

void Game::movePawn(int destX, int destY, int pawnX, int pawnY) {
    this->getBoardMutable().movePawn(destX, destY, pawnX, pawnY);
}