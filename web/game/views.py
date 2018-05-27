## @file game/views.py

"""
calc library interface to client

export calculation results to client
"""
from . import game
import logging
# todo move state to state.py
BOARD_WIDTH = 8
BOARD_HEIGHT = 8
import pdb;
class State:
    """
    State of the game
    """
    def __init__(self):
        self.init_game()

    def init_game(self):
        self._game = game.Game()

    def validate_move(self, destination_x, destination_y, pawn_x, pawn_y):
        is_valid = self._game.validateMove(destination_x, destination_y, pawn_x, pawn_y)

        if is_valid:
            self._game.movePawn(destination_x, destination_y, pawn_x, pawn_y)

        can_remove = self._game.canRemove(destination_x, destination_y, pawn_x, pawn_y)
        if can_remove:
            logging.warning("can_remove")
            logging.warning(can_remove)
            self._game.removePawn(destination_x, destination_y, pawn_x, pawn_y)

        return is_valid

    def can_move(self, pawn_field_x, pawn_field_y):
        can_move = self._game.canMove(pawn_field_x, pawn_field_y)

        return can_move

    def get_board(self):
        result = []
        board = self._game.getBoard()
        for y in range(0, BOARD_HEIGHT):
            result.append([])
            for x in range(0, BOARD_WIDTH):
                field = board.getField(x, y)
                serialized = {
                    'hasPawn': field.hasPawn(),
                    'isGameField': field.isGameField(),
                    'position': {
                        'x': field.getX(),
                        'y': field.getY()
                    }
                }
                if field.hasPawn():
                    pawn = field.getPawn()
                    serialized['pawn'] = {}
                    serialized['pawn']['isAlive'] = pawn.isAlive()
                    serialized['pawn']['isQueen'] = pawn.isQueen()
                    serialized['pawn']['color'] = pawn.getColor()
                    serialized['pawn']['x'] = pawn.getX()
                    serialized['pawn']['y'] = pawn.getY()
                result[y].append(serialized)
        return result

    def restart_game(self):
        self._game.restartGame()

_game_state_singleton = State()


def get_game_state():
    return _game_state_singleton


def getBoard(_):

    board = get_game_state().get_board()
    return {
        "board": board,
    }


def restartGame(_):
    get_game_state().restart_game()

def canMove(params):
    pawn_field_x = int(params["pawnFieldX"])
    pawn_field_y = int(params["pawnFieldY"])
    can_move = get_game_state().can_move(pawn_field_x, pawn_field_y)

    return {
        'canMove': can_move
    }

def handleMove(params):

    destination_x = int(params["destinationX"])
    destination_y = int(params["destinationY"])
    pawn_x = int(params["pawnX"])
    pawn_y = int(params["pawnY"])

    is_moved = get_game_state().validate_move(destination_x, destination_y, pawn_x, pawn_y)

    return {
        'isMoved': is_moved
    }















































