#ifndef BOARD_HPP
#define BOARD_HPP

#include <utility>
#include "../../util.hpp"
#include "field/field.hpp"

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
class GAME_STATE_DLL( Board ) {
    typedef Array2D<Field, 8, 8> BoardMatrix;
    BoardMatrix boardMatrix_;

public:

    static const unsigned WIDTH = 8;
    static const unsigned HEIGHT = 8;
    const Field& getField(int x, int y) const;

    //    todo: board should be singleton class
    Board();

private:
    void initializeBoard();

//    Board(const Board&) = delete;
//    Board& operator=(const Board&) = delete;
};


#endif //BOARD_HPP

