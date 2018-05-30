//
// Created by mateusz on 17.05.18.
//

#include "./board.h"
#include "player.h"
#include <memory>

using namespace std;

#ifndef GAME_H
#define GAME_H

#ifdef GAME_EXPORTS
//Workaround for Windows DLL library exports
#define FASADA_DLL(X) __declspec(dllexport)X
#else
//Workaround for Unix Shared Library exports
#define GAME_DLL(X) X
#endif

typedef shared_ptr<Field> PField;
typedef shared_ptr<Pawn> PPawn;

class GAME_DLL(Game) {
public:
    static Game& getInstance();
    void const initGame();
    void restartGame();

    const Board& getBoard() const;
    Board& getBoardMutable();
    Game();
    Game(Game const &) = delete;
    void operator=(Game const &) = delete;
    Player getPlayer() const;
    bool validateMove(int destX, int destY, int pawnX, int pawnY) const;
    bool canRemove(int destX, int destY, int pawnX, int pawnY) const;
    bool fieldOnBoard(int x, int y);
    bool fieldToKillOnBoard(int x, int y);
    bool goingInValidDirection(PField pawnField, PField destinationField);
    bool checkField(PField pawnField, int x, int y);
    bool checkQueenDirection(PField pawnField, int x, int y);

    bool validDistance(PField pawnField, PField destField) const;
    bool validQueenDistance(PField pawnField, PField destField) const;
    void movePawn(int destX, int destY, int pawnX, int pawnY);
    bool checkDirection(int yDiff, Color color) const;
    bool isKilling(const PField pawnField, const PField destField) const;
    bool isQueenKilling(const PField pawnField, const PField destField) const;
    void removePawn(int destX, int destY, int pawnX, int pawnY);
    bool canMove(int x, int y);
    bool canQueenMove(int x, int y);
    bool hasOneEnemyOnPath(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY, int directionX, int directionY);
    bool canGoToField(PField pawnField, PField destinationField);

private:
    Board board_;
    Player player_;
    Player enemy_;
};


#endif //GAME_H
