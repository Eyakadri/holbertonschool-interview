#!/usr/bin/python3
"""
Module that calculates the amount of rainwater retained
after it rains on a landscape represented by wall heights.
"""


def rain(walls):
    """
    Calculates total amount of rainwater retained.

    Args:
        walls (list): List of non-negative integers representing wall heights.

    Returns:
        int: Total units of retained rainwater.
    """
    if not walls:
        return 0

    n = len(walls)
    water = 0

    left = 0
    right = n - 1
    left_max = 0
    right_max = 0

    while left < right:
        if walls[left] < walls[right]:
            if walls[left] >= left_max:
                left_max = walls[left]
            else:
                water += left_max - walls[left]
            left += 1
        else:
            if walls[right] >= right_max:
                right_max = walls[right]
            else:
                water += right_max - walls[right]
            right -= 1
    return water
