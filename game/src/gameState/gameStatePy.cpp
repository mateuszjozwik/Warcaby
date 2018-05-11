/**
 * \file calcpy.cpp
 * \brief the Python interface for C++ calculation library
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//msvc disable warnings for Boost.Python
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4512)
#endif


#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "gameState.hpp"
#include "../position.hpp"
#include "../gameElements/board/board.hpp"
#include "../gameElements/board/field/field.hpp"
#include "../gameElements/pawn/pawn.hpp"

using namespace boost::python;

namespace {
    std::shared_ptr<Position> createPosition(unsigned x, unsigned y) {
        return std::shared_ptr<Position>(new Position{x, y});
    }
}

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( game )
{

        class_<GameState>("GameState")
            .def("startGame", &GameState::startGame)
            .def("getBoard", &GameState::getBoard, return_value_policy<reference_existing_object>())
            .def("handleMove", &GameState::handleMove)
            .def("isGameFinished", &GameState::isGameFinished)
            .def("isGameStarted", &GameState::isGameStarted)
            .def("validateMove", &GameState::validateMove);

        class_<Board>("Board")
            .def("getField", &Board::getField, return_value_policy<reference_existing_object>());

        class_<Position, std::shared_ptr<Position>>("Position")
            .def("__init__", make_constructor(&createPosition))
            .def("getX", &Position::getX)
            .def("getY", &Position::getY)
            ;

        class_<Pawn>("Pawn")
            .def("getColor", &Pawn::getColor)
            .def("isAlive", &Pawn::isAlive)
            .def("isQueen", &Pawn::isQueen)
            .def("getPosition", &Pawn::getPosition, return_value_policy<copy_const_reference>())
            ;

        class_<Field>("Field")
            .def("hasPawn", &Field::hasPawn)
            ;
}