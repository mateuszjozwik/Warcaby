#include "board.h"
#include "game.h"
#include <iostream>

const unsigned Board::WIDTH;
const unsigned Board::HEIGHT;

static const unsigned WIDTH = 8;
static const unsigned HEIGHT = 8;
typedef Array2D<Field, WIDTH, HEIGHT> BoardMatrix;

Board::Board() {
    bool isGameField;
    for (unsigned int x = 0; x < WIDTH; ++x) {
        isGameField = (x%2!=0);
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            boardMatrix_[x][y].setIsGameField(isGameField);
            boardMatrix_[x][y].setX(x);
            boardMatrix_[x][y].setY(y);

            isGameField = !isGameField;
        }
    }
}

BoardMatrix& Board::getBoardMatrix() {
    return boardMatrix_;
}

void Board::resetBoard(Player &player_) {
    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            boardMatrix_[x][y].setPawn(nullptr);
            boardMatrix_[x][y].setHasPawn(false);
        }
    }

    std::array<Pawn, 12>* pawns = player_.getPlayerPawns();

    for (Pawn& pawn: pawns->_M_elems) {
        pawn.setX(-1);
        pawn.setY(-1);
        pawn.initY(-1);
        pawn.setQueen(false);
    }
}

const Field& Board::getField(int x, int y) const {
    if (x >= 8 || y >= 8) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return boardMatrix_[x][y];
}

void Board::movePawn(int newX, int newY, int oldX, int oldY) {
    if (oldX >= 8 || oldY >= 8 || newX >= 8 || newY >= 8) {
        throw std::invalid_argument("Invalid coordinates");
    };

    Pawn& pawn = boardMatrix_[oldX][oldY].getPawn();

    boardMatrix_[newX][newY].setPawn(&pawn);
    boardMatrix_[newX][newY].setHasPawn(true);
    pawn.setX(newX);
    pawn.setY(newY);

    if ((newY > oldY && newY == 7 && pawn.getInitY() < 4)
        || (newY < oldY && newY == 0) && pawn.getInitY() > 4 ) {
        pawn.setQueen(true);
    }

    boardMatrix_[oldX][oldY].setHasPawn(false);
    boardMatrix_[oldX][oldY].setPawn(nullptr);
}

void Board::removePawn(int x, int y) {
    if (x >= 8 || y >= 8) {
        throw std::invalid_argument("Invalid coordinates");
    };

    Pawn& pawn = boardMatrix_[x][y].getPawn();
    pawn.kill();
    boardMatrix_[x][y].setHasPawn(false);
    boardMatrix_[x][y].setPawn(nullptr);
}

void Board::setPawns(Player &player_, Player &enemy_) {

    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            if (y<3 && ((x%2 != 0 && y%2==0) || (x%2 == 0 && y%2!=0))) {
                std::array<Pawn, 12>* pawns = player_.getPlayerPawns();
                for (Pawn& pawn: pawns->_M_elems) {
                    if (pawn.getY() < 0) {
                        pawn.setX(x);
                        pawn.setY(y);
                        pawn.initY(y);
                        boardMatrix_[x][y].setPawn(&pawn);
                        boardMatrix_[x][y].setHasPawn(true);

                        break;
                    }
                }
            }

            if ((y>4) && ((x%2==0 && y%2!=0) || (x%2!=0 && y%2==0))) {
                std::array<Pawn, 12>* pawns = enemy_.getPlayerPawns();
                for (Pawn& pawn: pawns->_M_elems) {
                    if (pawn.getY() < 0) {
                        pawn.setX(x);
                        pawn.setY(y);
                        pawn.initY(y);
                        pawn.setColor(Color::BLACK);
                        boardMatrix_[x][y].setPawn(&pawn);
                        boardMatrix_[x][y].setHasPawn(true);

                        break;
                    }
                }
            }
        }
    }
}

void Board::addPawn(Player &player_, int x, int y, Color color) {
    if (boardMatrix_[x][y].isGameField() == true) {
        std::array<Pawn, 12> *pawns = player_.getPlayerPawns();
        for (Pawn &pawn: pawns->_M_elems) {
            if (pawn.getY() < 0) {
                pawn.setX(x);
                pawn.setY(y);
                pawn.initY(y);
                pawn.setColor(color);
                boardMatrix_[x][y].setPawn(&pawn);
                boardMatrix_[x][y].setHasPawn(true);

                break;
            }
        }
    } else {
        throw std::invalid_argument("Can not add pawn on this field");
    }
}

void Board::clearBoard() {
    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            boardMatrix_[x][y].setPawn(nullptr);
            boardMatrix_[x][y].setHasPawn(false);
        }
    }
}

void Board::updateKills() {
    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            if (boardMatrix_[x][y].hasPawn()) {
                boardMatrix_[x][y].getPawn().setJustKilled(false);
            }
        }
    }
}