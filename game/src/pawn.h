//
// Created by mateusz on 18.05.18.
//

#ifndef PAWN_H
#define PAWN_H

#include "color.h"
#include "position.h"

#ifdef GAME_STATE_EXPORTS
/** Workaround for Windows DLL library exports */
#define GAME_STATE_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define GAME_STATE_DLL(X) X
#endif


class GAME_STATE_DLL( Pawn ) {
    bool isAlive_;
    Color color_;
    bool isQueen_;
    int posx_;
    int posy_;
public:
    Pawn(Color color_ = Color::WHITE, bool isAlive_ = true, bool isQueen_ = false, int posx_ = -1, int posy_ = -1);
    ~Pawn();
    Color getColor() const;
    void setColor(Color color);
    bool isAlive() const;
    bool isQueen() const;
    void promoteToQueen();
    void kill();
    void setPosition(int x, int y);
    int getX();
    int getY();

};


#endif //PAWN_H