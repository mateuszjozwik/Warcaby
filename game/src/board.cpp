#include "board.h"
#include "game.h"
#include <iostream>

const unsigned Board::WIDTH;
const unsigned Board::HEIGHT;

Board::Board() {
    std::cout << "create Board" << std::endl;

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

const Field& Board::getField(int x, int y) const {
    if (x >= WIDTH || y >= HEIGHT) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return boardMatrix_[x][y];
}

void Board::movePawn(int newX, int newY, int oldX, int oldY) {
    if (oldX >= WIDTH || oldY >= HEIGHT || newX >= WIDTH || newY >= HEIGHT) {
        throw std::invalid_argument("Invalid coordinates");
    };

    boardMatrix_[newX][newY].setPawn(&boardMatrix_[oldX][oldY].getPawn());
    boardMatrix_[newX][newY].setHasPawn(true);

    boardMatrix_[oldX][oldY].setHasPawn(false);
    boardMatrix_[oldX][oldY].setPawn(nullptr);
}

void Board::setPawns(Player &player_) {

    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            if (y<3 && ((x%2 != 0 && y%2==0) || (x%2 == 0 && y%2!=0))) {

                std::array<Pawn, 12>* pawns = player_.getPlayerPawns();

                for (Pawn& pawn: pawns->_M_elems) {
                    if (pawn.getY() < 0 && pawn.getX() < 8) {
                        pawn.setX(x);
                        pawn.setY(y);
                        boardMatrix_[x][y].setPawn(&pawn);
                        boardMatrix_[x][y].setHasPawn(true);

                        break;
                    }
                }

            }

            if ((y>4) && ((x%2==0 && y%2!=0) || (x%2!=0 && y%2==0))) {
//                boardMatrix_[x][y].setPawn(new Pawn(Color::WHITE));
            }
        }
    }
}