#include <boost/test/unit_test.hpp>

#include "../src/board.h"
#include "../src/game.h"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE(board_test)

BOOST_AUTO_TEST_CASE(CheckAddPawn) {
        Player player_;
        Player enemy_;
        Board board_;
        board_.addPawn(player_, 1, 0, Color::WHITE);
        BOOST_CHECK(board_.getField(1, 0).hasPawn());
        BOOST_CHECK(!board_.getField(2, 1).hasPawn());
}

BOOST_AUTO_TEST_SUITE_END()












