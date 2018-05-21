//
// Created by mateusz on 17.05.18.
//

#include "./board.h"
#include "player.h"
#ifndef GAME_H
#define GAME_H

#ifdef GAME_EXPORTS
//Workaround for Windows DLL library exports
#define FASADA_DLL(X) __declspec(dllexport)X
#else
//Workaround for Unix Shared Library exports
#define GAME_DLL(X) X
#endif

class GAME_DLL(Game) {
public:
    static Game& getInstance();
    void const initGame();
    Board& getBoard();
    Game();
//    todo: this should not be commented
    Game(Game const &) = delete;
    void operator=(Game const &) = delete;
    Player getPlayer();
private:
    Board board_;
    Player player_;
};


#endif //GAME_H
