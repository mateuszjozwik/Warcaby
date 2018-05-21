#include "game.h"
#include "iostream"
#include <iostream>

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

Board& Game::getBoard() {
    return board_;
}

Player Game::getPlayer() {
    return player_;
}