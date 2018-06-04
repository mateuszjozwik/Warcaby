#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(pawn_test)

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

BOOST_AUTO_TEST_CASE(AssertPawnCanMove) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(Game::getInstance().canMove(1, 0));
        BOOST_CHECK(Game::getInstance().validateMove(0, 1, 1, 0));
        Game::getInstance().movePawn(0, 1, 1, 0);
        BOOST_CHECK(!Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(Game::getInstance().getBoard().getField(0, 1).hasPawn());
}

BOOST_AUTO_TEST_CASE(AssertCanNotMoveToOccupied) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        Game::getInstance().getBoardMutable().addPawn(player_, 0, 1, Color::BLACK);
        BOOST_CHECK(!Game::getInstance().validateMove(0, 1, 1, 0));
        Game::getInstance().movePawn(0, 1, 1, 0);
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(Game::getInstance().getBoard().getField(0, 1).hasPawn());
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).getPawn().getColor() == Color::WHITE);
        BOOST_CHECK(Game::getInstance().getBoard().getField(0, 1).getPawn().getColor() == Color::BLACK);
}

BOOST_AUTO_TEST_CASE(AssertCanNotMoveToRemoteLocation) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(!Game::getInstance().validateMove(4, 3, 1, 0));
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(!Game::getInstance().getBoard().getField(4, 3).hasPawn());
}

BOOST_AUTO_TEST_CASE(AssertCanNotMoveHorizontal) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(!Game::getInstance().validateMove(3, 0, 1, 0));
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(!Game::getInstance().getBoard().getField(3, 0).hasPawn());
}

BOOST_AUTO_TEST_CASE(AssertCanNotMoveVertical) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(!Game::getInstance().validateMove(1, 2, 1, 0));
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(!Game::getInstance().getBoard().getField(1, 2).hasPawn());
}

BOOST_AUTO_TEST_CASE(AssertCanNotMoveToNonGameField) {
        Player player_;
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(!Game::getInstance().validateMove(2, 0, 1, 0));
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(!Game::getInstance().getBoard().getField(2, 0).hasPawn());
}

BOOST_AUTO_TEST_CASE(AssertPromotionToQueen) {
        Player player_;
        Game::getInstance().getBoardMutable().clearBoard();
        Game::getInstance().getBoardMutable().addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(Game::getInstance().getBoard().getField(1, 0).hasPawn());
        BOOST_CHECK(Game::getInstance().canMove(1, 0));

        BOOST_CHECK(Game::getInstance().validateMove(2, 1, 1, 0));
        Game::getInstance().movePawn(2, 1, 1, 0);
        BOOST_CHECK(Game::getInstance().getBoard().getField(2 ,1).hasPawn());

        BOOST_CHECK(Game::getInstance().validateMove(3, 2, 2, 1));
        Game::getInstance().movePawn(3, 2, 2, 1);
        BOOST_CHECK(Game::getInstance().getBoard().getField(3 ,2).hasPawn());

        BOOST_CHECK(Game::getInstance().validateMove(4, 3, 3, 2));
        Game::getInstance().movePawn(4, 3, 3, 2);
        BOOST_CHECK(Game::getInstance().getBoard().getField(4, 3).hasPawn());

        BOOST_CHECK(Game::getInstance().validateMove(5, 4, 4, 3));
        Game::getInstance().movePawn(5, 4, 4, 3);
        BOOST_CHECK(Game::getInstance().getBoard().getField(5, 4).hasPawn());

        BOOST_CHECK(Game::getInstance().validateMove(6, 5, 5, 4));
        Game::getInstance().movePawn(6, 5, 5, 4);
        BOOST_CHECK(Game::getInstance().getBoard().getField(6, 5).hasPawn());

        BOOST_CHECK(Game::getInstance().validateMove(7, 6, 6, 5));
        Game::getInstance().movePawn(7, 6, 6, 5);
        BOOST_CHECK(Game::getInstance().getBoard().getField(7, 6).hasPawn());

        BOOST_CHECK(!Game::getInstance().getBoard().getField(7 ,6).getPawn().isQueen());
        BOOST_CHECK(Game::getInstance().validateMove(6 ,7, 7, 6));
        Game::getInstance().movePawn(6 ,7, 7, 6);
        BOOST_CHECK(Game::getInstance().getBoard().getField(6 ,7).hasPawn());
        BOOST_CHECK(Game::getInstance().getBoard().getField(6 ,7).getPawn().isQueen());
}

BOOST_AUTO_TEST_SUITE_END()












