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

class State:
    """
    State of the game
    """
    def __init__(self):
        self.init_game()

    def init_game(self):
        self._game = game.GameState()

    def start_game(self):
        return self._game.startGame()

    def is_game_finished(self):
        return self._game.isGameFinished()

    def is_game_started(self):
        return self._game.isGameStarted()

    def get_board(self):
        result = []
        board = self._game.getBoard()
        for y in range(0, BOARD_HEIGHT):
            result.append([])
            for x in range(0, BOARD_WIDTH):
                field = board.getField(x, y)
                serialized = {
                    'hasPawn': str(field.hasPawn()),
                }
                if field.hasPawn():
                    pawn = field.getPawn()
                    serialized['isAlive'] = str(pawn.isAlive())
                    serialized['color'] = str(pawn.getColor())
                    serialized['isQueen'] = str(pawn.isQueen())
            result[y].append(serialized)
        return result


_game_state_singleton = State()


def get_game_state():
    return _game_state_singleton


def startGame(params):
    return {
        "initGame": get_game_state().start_game()
    }


def handleMove(params):
    return {
        "handleMove ": True
    }


def isGameFinished(params):
    return {
        "isGameFinished": get_game_state().is_game_finished()
    }


def isGameStarted(params):
    return {
        "isGameStarted": get_game_state().is_game_started()
    }


def validateMove(params):
    return {
        "validateMove": True
    }


def getBoard(_):

    board = get_game_state().get_board()
    result = []
    for row in board:
        result_row = {"cells": []}
        for cell in row:
            result_row["cells"].append(cell)
        result.append(result_row)
    return {
        "board": result,
    }