#!/usr/bin/python3
"""
N queens solver using backtracking with position conflict checks.
"""

import sys

board_size = 0
results = []
positions = None


def read_and_validate_args():
    """
    Read the board size argument from command line, validate it.

    Returns:
        int: The validated board size.
    """
    global board_size
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)
    try:
        board_size = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)
    if board_size < 4:
        print("N must be at least 4")
        sys.exit(1)
    return board_size


def can_attack(pos_a, pos_b):
    """
    Determine if two queens attack each other.

    Args:
        pos_a (list or tuple): Coordinates [row, col] of queen A.
        pos_b (list or tuple): Coordinates [row, col] of queen B.

    Returns:
        bool: True if queens can attack each other, False otherwise.
    """
    same_row = pos_a[0] == pos_b[0]
    same_col = pos_a[1] == pos_b[1]
    same_diag = abs(pos_a[0] - pos_b[0]) == abs(pos_a[1] - pos_b[1])
    return same_row or same_col or same_diag


def solution_already_recorded(candidate):
    """
    Check if a solution is already stored in results.

    Args:
        candidate (list): Candidate solution list of positions.

    Returns:
        bool: True if solution already exists, False otherwise.
    """
    for sol in results:
        if all(any(p[0] == c[0] and p[1] == c[1] for p in sol) for c in candidate):
            return True
    return False


def find_solutions(row=0, current_positions=None):
    """
    Recursive backtracking function to find all valid queen placements.

    Args:
        row (int): Current row to place a queen.
        current_positions (list): Positions of placed queens so far.
    """
    if current_positions is None:
        current_positions = []

    global board_size, positions, results

    if row == board_size:
        # If this arrangement is new, add to results
        if not solution_already_recorded(current_positions):
            results.append(current_positions.copy())
        return

    for col in range(board_size):
        candidate_pos = positions[row * board_size + col]
        if not any(can_attack(candidate_pos, placed) for placed in current_positions):
            current_positions.append(candidate_pos)
            find_solutions(row + 1, current_positions)
            current_positions.pop()


def main():
    global positions, board_size

    board_size = read_and_validate_args()
    positions = [[i // board_size, i % board_size] for i in range(board_size ** 2)]
    find_solutions()

    for sol in results:
        print(sol)


if __name__ == "__main__":
    main()
