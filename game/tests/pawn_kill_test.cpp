#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(pawn_move_test)

//asserts that pawn can kill and enemy is removed after being killed
BOOST_AUTO_TEST_CASE(checkKillMove_scenario_1) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::BLACK);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
        Game::getInstance().validateMove(3, 2 ,1 ,0);
        BOOST_CHECK(Game::getInstance().canRemove(3, 2 ,1 ,0));
        Game::getInstance().movePawn(3, 2 ,1 ,0);
        Game::getInstance().removePawn(3, 2 ,1 ,0);
        BOOST_CHECK(!Game::getInstance().getBoard().getField(2, 1).hasPawn());
}

//asserts that it's possible to kill only enemy's pawns
BOOST_AUTO_TEST_CASE(checkKillMove_scenario_2) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::WHITE);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
        Game::getInstance().validateMove(3, 2 ,1 ,0);
        BOOST_CHECK(!Game::getInstance().canRemove(3, 2 ,1 ,0));
        Game::getInstance().movePawn(3, 2 ,1 ,0);
        BOOST_CHECK(Game::getInstance().getBoard().getField(2, 1).hasPawn());
}

BOOST_AUTO_TEST_SUITE_END()
