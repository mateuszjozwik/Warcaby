#include "gameState.hpp"

GameState::GameState(bool isGameFinished, bool isGameStarted) : isGameFinished_(isGameFinished), isGameStarted_(isGameStarted) {}

void GameState::startGame() {
    isGameStarted_ = true;
}

void GameState::handleMove() {

}

bool GameState::isGameFinished() const {
    return isGameFinished_;
}

bool GameState::isGameStarted() const {
    return isGameStarted_;
}

bool GameState::validateMove() {
    return false;
}

const Board &GameState::getBoard() const {
    return board_;
}