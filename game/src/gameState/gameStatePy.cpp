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

#include "../color.h"
#include "../game.h"
#include "../pawn.h"
#include "../field.h"
#include "../board.h"
#include "../player.h"

using namespace boost::python;

/** Python interface for Game
 */

class GameManagerPy {
public:
    Board& getBoard() {
        return Game::getInstance().getBoard();
    }
};

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( game )
        {
         enum_<Color>("Color")
                 .value("WHITE", Color::WHITE)
                 .value("BLACK", Color::BLACK);

//        class_<Game>("Game")
//            .def("getInstance", &Game::getInstance, return_value_policy<reference_existing_object>());
//            .def("getBoard", &Game::getBoard, return_value_policy<reference_existing_object>());

        class_<Board>("Board")
            .def("setPawns", &Board::setPawns)
            .def("getField", &Board::getField, return_value_policy<reference_existing_object>())
        ;

        class_<Pawn>("Pawn")
            .def("getX", &Pawn::getX)
            .def("getY", &Pawn::getY)
            .def("isAlive", &Pawn::isAlive)
            .def("isQueen", &Pawn::isQueen)
            .def("getColor", &Pawn::getColor)
            .def("kill", &Pawn::kill)
        ;

        class_<Field>("Field")
            .def("getX", &Field::getX)
            .def("getY", &Field::getY)
            .def("setY", &Field::setY)
            .def("setX", &Field::setX)
            .def("hasPawn", &Field::hasPawn)
            .def("getPawn", &Field::getPawn, return_value_policy<reference_existing_object>())
            .def("removePawn", &Field::removePawn)
            .def("isGameField", &Field::isGameField)
        ;

        class_<GameManagerPy>("Game")
            .def( "getBoard", &GameManagerPy::getBoard, return_value_policy<reference_existing_object>())
        ;

        }
