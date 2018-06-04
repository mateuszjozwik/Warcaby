#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

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
        Player player_;
        Player enemy_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(enemy_, 2, 1, Color::BLACK);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
}

BOOST_AUTO_TEST_SUITE_END()












