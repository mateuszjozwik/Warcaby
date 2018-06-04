/**
   calc library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(game_test)

BOOST_AUTO_TEST_CASE(InitGameEmptyBoard) {
        Board b = Game::getInstance().getBoard();
        for(unsigned x = 0; x<Board::WIDTH; ++x) {
            for(unsigned y = 0; y<Board::HEIGHT; ++y){
                BOOST_CHECK(!b.getBoardMatrix()[x][y].hasPawn());
            }
        }
}

BOOST_AUTO_TEST_CASE(DefaultEmptyBoard) {
    Board b;
    for(unsigned x = 0; x<Board::WIDTH; ++x) {
        for(unsigned y = 0; y<Board::HEIGHT; ++y){
            BOOST_CHECK(!b.getBoardMatrix()[x][y].hasPawn());
        }
    }
}

BOOST_AUTO_TEST_CASE(Assert24PawnsOnBoard) {
        Player player;
        Player enemy;
        Board b;
        b.setPawns(player, enemy);
        int counter = 0;
        for(unsigned x = 0; x<Board::WIDTH; ++x) {
            for(unsigned y = 0; y<Board::HEIGHT; ++y) {
                if (b.getField(x, y).hasPawn()) {
                    ++counter;
                }
            }
        }
        BOOST_CHECK(counter == 24);
}

BOOST_AUTO_TEST_CASE(Assert12WhitePawnsOnBoard) {
        Player player;
        Player enemy;
        Board b;
        b.setPawns(player, enemy);

        int whitePawnsCounter = 0;
        for(unsigned x = 0; x<Board::WIDTH; ++x) {
            for(unsigned y = 0; y<Board::HEIGHT; ++y) {
                if (b.getField(x, y).hasPawn()) {
                    if (b.getField(x, y).getPawn().getColor() == Color::WHITE) {
                        ++whitePawnsCounter;
                    }
                }
            }
        }
        BOOST_CHECK(whitePawnsCounter == 12);
}

BOOST_AUTO_TEST_CASE(Assert12BlackPawnsOnBoard) {
        Player player;
        Player enemy;
        Board b;
        b.setPawns(player, enemy);

        int blackPawnsCounter = 0;
        for(unsigned x = 0; x<Board::WIDTH; ++x) {
            for(unsigned y = 0; y<Board::HEIGHT; ++y) {
                if (b.getField(x, y).hasPawn()) {
                    if (b.getField(x, y).getPawn().getColor() == Color::BLACK) {
                        ++blackPawnsCounter;
                    }
                }
            }
        }
        BOOST_CHECK(blackPawnsCounter == 12);
}

BOOST_AUTO_TEST_CASE(Assert32GameField) {
        Board b;

        int gameFieldCounter = 0;
        for(unsigned x = 0; x<Board::WIDTH; ++x) {
            for(unsigned y = 0; y<Board::HEIGHT; ++y) {
                if (b.getField(x, y).isGameField()) {
                    gameFieldCounter++;
                }
            }
        }
        BOOST_CHECK(gameFieldCounter == 32);
}

BOOST_AUTO_TEST_SUITE_END()





