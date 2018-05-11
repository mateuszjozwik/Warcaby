#include "board.hpp"

const unsigned Board::WIDTH;
const unsigned Board::HEIGHT;

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
    for (unsigned int x = 0; x < WIDTH; ++x) {
        for (unsigned int y = 0; y < HEIGHT; ++y) {
            boardMatrix_[x][y] = {Position(x, y)};
        }
    }
}

const Field &Board::getField(int x, int y) const {
    if (x >= WIDTH || y >= HEIGHT) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return boardMatrix_[x][y];
}