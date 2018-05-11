#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../gameElements/board/board.hpp"

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//msvc disable warnings for sheduler_ and history_ member
#pragma warning(disable:4251)
#endif


#ifdef GAME_STATE_EXPORTS
/** Workaround for Windows DLL library exports */
#define GAME_STATE_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define GAME_STATE_DLL(X) X
#endif

/**
   game state representation
*/
class GAME_STATE_DLL( GameState ) {

    Board board_;

    bool isGameFinished_;
    bool isGameStarted_;
public:
    GameState(bool isGameFinished = false, bool isGameStarted = false);
    GameState(Board board, bool isGameFinished = false, bool isGameStarted = false);

    const Board& getBoard() const;

    bool isGameStarted() const;

    bool isGameFinished() const;

    void startGame();

    bool validateMove();

    void handleMove();
};


#endif //GAME_STATE_HPP
