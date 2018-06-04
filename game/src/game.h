//
// Created by mateusz on 17.05.18.
//

#include "./board.h"
#include "player.h"
#include "color.h"
#include <memory>

using namespace std;

#ifndef GAME_H
#define GAME_H

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

typedef shared_ptr<Field> PField;
typedef shared_ptr<Pawn> PPawn;

class GAME_STATE_DLL( Game ) {
public:
    static Game& getInstance();
    void const initGame();
    void restartGame();

    const Board& getBoard() const;
    Board& getBoardMutable();
    Game();
    Game(Game const &) = delete;
    void operator=(Game const &) = delete;

    /// @returns true if move can be performed
    bool validateMove(int destX, int destY, int pawnX, int pawnY) const;

    /// @returns true if pawn can be removed
    bool canRemove(int destX, int destY, int pawnX, int pawnY) const;

    /// @returns true if field is in scope of the board
    bool fieldOnBoard(int x, int y);

    /// @returns true if pawn is going in correct direction
    bool goingInValidDirection(PField pawnField, PField destinationField);

    /// @returns true if pawn can go in direction specified by x and y
    bool checkMove(PField pawnField, int x, int y);

    /// @returns true if Queen can go in direction specified by x and y
    bool checkQueenMove(PField pawnField, int x, int y);

    /// @returns true if distance between current and destination field is correct
    bool validDistance(PField pawnField, PField destField) const;

    void movePawn(int destX, int destY, int pawnX, int pawnY);
    bool checkDirection(int yDiff, Color color) const;
    bool isKilling(const PField pawnField, const PField destField) const;
    void removePawn(int destX, int destY, int pawnX, int pawnY);
    bool canMove(int x, int y);
    int pawnsOnPath(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY, bool countEnemies = false) const;
    void removePawnByQueen(int pawnX, int pawnY, int fieldToGoX, int fieldToGoY);
    bool canKill(PField pawnField, int x, int y);
    bool canPawnKill(int x, int y);
    bool canPlayerKill(Color color) const;

    bool lastMoveKilled();
    void setLastMoveKilled(bool lastMoveKilled);

    Color getLastMoveColor();
    void setLastMoveColor(Color color);

private:
    Board board_;
    Player player_;
    Player enemy_;
    Color lastMoveColor_;
    bool lastMoveKilled_;
};


#endif //GAME_H
