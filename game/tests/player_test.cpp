#include <boost/test/unit_test.hpp>

#include "../src/board.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(player_test)

BOOST_AUTO_TEST_CASE(PlayersPawnsAmount) {
        Player player;
        std::array<Pawn, 12>* pawns = player.getPlayerPawns();
        BOOST_CHECK(pawns->size() == 12);
}

BOOST_AUTO_TEST_CASE(DefaultPlayerCanNotkill) {
        Player player;
        std::array<Pawn, 12>* pawns = player.getPlayerPawns();
        BOOST_CHECK(pawns->size() == 12);
}

BOOST_AUTO_TEST_CASE(AssertWhiteCanStart) {
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

BOOST_AUTO_TEST_SUITE_END()






//board_.addPawn(player_, 1, 0, Color::WHITE);
//board_.addPawn(enemy_, 2, 1, Color::BLACK);
