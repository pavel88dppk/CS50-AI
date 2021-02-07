"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    xcounter = 0
    ocounter = 0
    for i in range(len(board)):
        for y in range(len(board[i])):
            if board[i][y] == X:
                xcounter += 1
            elif board[i][y] == O:
                ocounter += 1
    if xcounter == ocounter:
        return X
    elif xcounter > ocounter:
        return O
    else:
        return None


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    actions = set()
    falsecounter = 0
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == EMPTY:
                action = (i, j)
                actions.add(action)
            else:
                falsecounter += 1
    if falsecounter == 9:
        return None
    else:
        return actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    new_board = copy.deepcopy(board)
    if action[0] > 3 or action[1] > 3:
        raise ValueError
    else:
        new_board[action[0]][action[1]] = player(board)

    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for i in range(len(board)):
        if board[i][0] == board[i][1] == board[i][2]:
            if board[i][0] == X:
                return X
            elif board[i][0] == O:
                return O
            else:
                return None
        for j in range(len(board)):
            if board[0][j] == board[1][j] == board[2][j]:
                if board[0][j] == X:
                    return X
                elif board[0][j] == O:
                    return O
                else:
                    return None

    if board[0][0] == board[1][1] == board[2][2]:
        if board[0][0] == X:
            return X
        elif board[0][0] == O:
            return O
        else:
            return None
    elif board[0][2] == board[1][1] == board[2][0]:
        if board[0][2] == X:
            return X
        elif board[0][2] == O:
            return O
        else:
            return None

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """

    if winner(board):
        return True
    else:
        notemptycounter = 0
        for i in range(len(board)):
            for j in range(len(board[i])):
                if board[i][j] != EMPTY:
                    notemptycounter += 1
                else:
                    return False
        if notemptycounter == 9:
            return True
    return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if terminal(board):
        if winner(board) == X:
            return 1
        elif winner(board) == O:
            return -1
        else:
            return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    else:
        if player(board) == X:
            value, move = max_value(board)
        else:
            value, move = min_value(board)

    return move


def max_value(board):
    """
    Returns the max value a player may desire at a certain instant
    """
    if terminal(board):
        return utility(board), None

    else:
        maxv = -2
        move = None

        for action in actions(board):
            m, x = min_value(result(board, action))

            if m > maxv:
                maxv = m
                move = action

                if maxv == 1:
                    return maxv, move

        return maxv, move


def min_value(board):
    """
    Returns the min value a player may desire at a certain instant
    """
    if terminal(board):
        return utility(board), None

    else:
        minv = 2
        move = None

        for action in actions(board):
            m, x = max_value(result(board, action))

            if m < minv:
                minv = m
                move = action

                if minv == -1:
                    return minv, move

        return minv, move
