#!/usr/bin/python3
"""
Rain water trapping algorithm module.
"""


def rain(walls):
    """
    Calculate how many square units of water will be retained after it rains.

    Given a list of non-negative integers representing the heights of walls
    with unit width 1, calculate the total amount of rainwater that can be
    trapped between the walls.

    Args:
        walls (list): List of non-negative integers representing wall heights.

    Returns:
        int: Total amount of rainwater retained.

    The algorithm works by finding the maximum height to the left and right
    of each position, then calculating the water level at each position as
    the minimum of these two maximums minus the current wall height.
    """
    if not walls or len(walls) < 3:
        return 0

    n = len(walls)
    total_water = 0

    # Find maximum height to the left of each position
    left_max = [0] * n
    left_max[0] = walls[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i - 1], walls[i])

    # Find maximum height to the right of each position
    right_max = [0] * n
    right_max[n - 1] = walls[n - 1]
    for i in range(n - 2, -1, -1):
        right_max[i] = max(right_max[i + 1], walls[i])

    # Calculate water trapped at each position
    for i in range(n):
        # Water level is minimum of left and right maximums
        water_level = min(left_max[i], right_max[i])
        # Water trapped is water level minus current wall height
        if water_level > walls[i]:
            total_water += water_level - walls[i]

    return total_water
