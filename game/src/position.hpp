#ifndef POSITION_HPP
#define POSITION_HPP

#include <limits>

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
class GAME_STATE_DLL( Position ) {
    static const unsigned DEFAULT_VALUE = 1;
    unsigned x_;
    unsigned y_;

public:
    Position(unsigned x = DEFAULT_VALUE, unsigned y = DEFAULT_VALUE);
    Position(const Position&) = default;

    Position(Position&&) = default;
    Position& operator =(Position&&) = default;
    Position& operator =(const Position&) = default;

    unsigned int getX() const;
    unsigned int getY() const;
};

#endif // POSITION_HPP
