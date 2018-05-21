//
// Created by mateusz on 18.05.18.
//

#ifndef FIELD_H
#define FIELD_H

#include "pawn.h"

#ifdef GAME_STATE_EXPORTS
/** Workaround for Windows DLL library exports */
#define GAME_STATE_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define GAME_STATE_DLL(X) X
#endif


class GAME_STATE_DLL( Field ) {
    unsigned int xPos_;
    unsigned int yPos_;
    bool hasPawn_;
    bool isGameField_;
    const Pawn* pawn_ = nullptr;

public:
    Field();
    Field(unsigned int xPos, unsigned int yPos, bool isGameField, bool hasPawn_ = false);

    int getX();
    int getY();

    void setX(int x);
    void setY(int y);

    const Pawn& getPawn() const;
    bool hasPawn();
    bool setPawn(const Pawn* pawn);
    bool removePawn();
    bool isGameField() const;
    void setIsGameField(bool isGameField);
};


#endif //FIELD_H
