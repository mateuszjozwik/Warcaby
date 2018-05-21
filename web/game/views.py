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
                        'x': str(field.getX()),
                        'y': str(field.getY())
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

        # boardResult = []
        # for row in result:
        #     result_row = {"cells": []}
        #     for cell in row:
        #         result_row["cells"].append(cell)
        #     boardResult.append(result_row)

        return result


_game_state_singleton = State()


def get_game_state():
    return _game_state_singleton

def getBoard(_):

    board = get_game_state().get_board()
    return {
        "board": board,
    }