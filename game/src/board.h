#ifndef BOARD_HPP
#define BOARD_HPP

#include <utility>
#include "util.h"
#include "field.h"
#include "color.h"
#include "pawn.h"
#include "position.h"
#include "player.h"

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


class GAME_STATE_DLL( Board ) {

public:
    Board();

    static const unsigned WIDTH = 8;
    static const unsigned HEIGHT = 8;
    const Field& getField(int x, int y) const;
    void setPawns(Player& player);
    void movePawn(int newX, int newY, int oldX, int oldY);
private:
    typedef Array2D<Field, WIDTH, HEIGHT> BoardMatrix;
    /// array of fields storing pieces
    BoardMatrix boardMatrix_;
};


#endif //BOARD_HPP

