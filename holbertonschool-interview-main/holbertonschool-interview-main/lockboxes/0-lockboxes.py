#!/usr/bin/python3
"""
Module 0-lockboxes
This module contains a function `canUnlockAll` that
determines if all boxes in a set can be unlocked.
"""


def canUnlockAll(boxes):
    """
    Determines if all the boxes can be opened.

    Args:
        boxes (list of lists): List where each index represents a
        box, and each value is a list of keys in that box.

    Returns:
        bool: True if all boxes can be opened, False otherwise.
    """
    n = len(boxes)
    opened = [False] * n
    opened[0] = True
    keys = set(boxes[0])

    while keys:
        new_key = keys.pop()
        if 0 <= new_key < n and not opened[new_key]:
            opened[new_key] = True
            keys.update(boxes[new_key])
    return all(opened)
