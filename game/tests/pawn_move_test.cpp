#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(pawn_move_test)

//assert than pawn can not be moved when there is no free field available
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_1) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::WHITE);
        BOOST_CHECK(!Game::getInstance().canMove(1, 0));
}

//assert than pawn can be moved when there's only right field available
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_2) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::WHITE);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
}

//assert than pawn be moved when there's only left field available
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_3) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
}

//assert than pawn be moved when there are two enemies on the way (one on the left and one on the right)
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_4) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::BLACK);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::BLACK);

        BOOST_CHECK(Game::getInstance().canMove(1, 0));
}

//assert than pawn can be moved when there are is one enemy on the way (left side), but further is the wall so kill is not possible
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_5) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::BLACK);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::WHITE);

        BOOST_CHECK(!Game::getInstance().canMove(1, 0));
}

//assert than pawn be moved when there are is one enemy on the way (right side)
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_6) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::BLACK);

        BOOST_CHECK(Game::getInstance().canMove(1, 0));
}

//assert than pawn can not be moved when there are enemies on the way but it's not possible to kill them
BOOST_AUTO_TEST_CASE(checkCanMove_scenario_7) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::BLACK);
        Game::getInstance().getBoardMutable().addPawn(player_, 2, 1, Color::BLACK);
        Game::getInstance().getBoardMutable().addPawn(player_, 3, 2, Color::BLACK);

        BOOST_CHECK(!Game::getInstance().canMove(1, 0));
}
BOOST_AUTO_TEST_SUITE_END()
