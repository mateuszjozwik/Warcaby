//
// Created by mateusz on 18.05.18.
//

#ifndef FIELD_H
#define FIELD_H

#include "pawn.h"

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


class GAME_STATE_DLL( Field ) {
    int xPos_;
    int yPos_;
    bool hasPawn_;
    bool isGameField_;
    Pawn* pawn_ = nullptr;

public:
    Field();
    Field(int xPos, int yPos, bool isGameField, bool hasPawn_ = false);

    int getXConst() const;
    int getYConst() const;

    int getX();
    int getY();

    void setX(int x);
    void setY(int y);


    Pawn& getPawn() const;
    bool hasPawn() const ;
    bool setPawn(Pawn* pawn);
    bool removePawn();
    bool isGameField() const;
    void setIsGameField(bool isGameField);
    void setHasPawn(bool hasPawn);

    void setPosition(int x, int y);
};


#endif //FIELD_H
