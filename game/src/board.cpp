#include "board.h"
#include "game.h"
#include <iostream>

const unsigned Board::WIDTH;
const unsigned Board::HEIGHT;

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

const Field& Board::getField(int x, int y) const {
    if (x >= WIDTH || y >= HEIGHT) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return boardMatrix_[x][y];
}

void Board::setPawns(Player &player_) {

    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            if (y<3 && ((x%2 != 0 && y%2==0) || (x%2 == 0 && y%2!=0))) {
                player_.getPlayerPawn()->setPosition(1, 1);

                std::array<Pawn, 12>* pawns = player_.getPlayerPawns();

                for (Pawn& pawn: pawns->_M_elems) {
                    if (pawn.getY() < 0 && pawn.getX()<0) {
                        pawn.setPosition(x, y);
                        boardMatrix_[x][y].setPawn(&pawn);

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