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
        self._game.initGame()

    # this function check all pre-requisitions for performing the move and if they are met, movement is performed
    def validate_move(self, destination_x, destination_y, pawn_x, pawn_y, must_kill):
        board = self._game.getBoard()

        # checks if it's possible to move pawn to selected destination
        is_valid = self._game.validateMove(destination_x, destination_y, pawn_x, pawn_y)
        # checks if performing selected move will result in killing enemy's pawn
        will_kill_pawn = self._game.canRemove(destination_x, destination_y, pawn_x, pawn_y)

        # if selected pawn can kill but it won't be result of current move, movement can not be performed
        if must_kill == 1 and not will_kill_pawn:
            return False

        # if movement is valid one, perform it
        if is_valid:
            player_color = board.getField(pawn_x, pawn_y).getPawn().getColor()
            # can_any_pawn_kill = self._game.canPlayerKill(player_color)
            # if not can_any_pawn_kill:
            self._game.setLastMoveColor(player_color)
            self._game.movePawn(destination_x, destination_y, pawn_x, pawn_y)

        self._game.setLastMoveKilled(False)
        # remove pawn from the board if performing selected move results in killing enemy's pawn
        if will_kill_pawn:
            self._game.removePawn(destination_x, destination_y, pawn_x, pawn_y)
            self._game.setLastMoveKilled(True)

        return is_valid

    # check if selected pawn can be moved and if it has an opportunity to kill enemy's pawn
    def can_move(self, x, y):

        board = self._game.getBoard()
        pawn = board.getField(x, y).getPawn()

        last_move_color = self._game.getLastMoveColor()
        selected_pawn_color = pawn.getColor()
        can_kill = self._game.canPlayerKill(last_move_color)
        last_move_killed = self._game.lastMoveKilled()

        if (last_move_color is selected_pawn_color and last_move_killed and can_kill) \
                or (last_move_color is not selected_pawn_color):

            # checks if selected Pawn can move in any direction
            can_move = self._game.canMove(x, y)

            # checks if selected Pawn has an opportunity to kill enemy's pawn
            can_kill = board.getField(x, y).getPawn().checkIfPawnCanKill()

            if not can_kill:
                can_any_pawn_kill = self._game.canPlayerKill(board.getField(x, y).getPawn().getColor())

                if can_any_pawn_kill and not can_kill:
                    can_move = False

            return {
                'canPawnKill': can_kill,
                'canMove': can_move
            }
        else:
            return {
                'canPawnKill': False,
                'canMove': False
            }

    # return array of fields with all 'front-end-required' information about each field
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

    return can_move


def handleMove(params):

    destination_x = int(params["destinationX"])
    destination_y = int(params["destinationY"])
    pawn_x = int(params["pawnX"])
    pawn_y = int(params["pawnY"])
    must_kill = int(params["canPawnKill"])

    is_moved = get_game_state().validate_move(destination_x, destination_y, pawn_x, pawn_y, must_kill)

    return {
        'isMoved': is_moved
    }















































