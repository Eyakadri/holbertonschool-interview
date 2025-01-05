#!/usr/bin/python3
"""
0-lockboxes Module

this module contains a function to determine if all boxes in a list
"""


def canUnlockAll(boxes):
    """
    checks if all boxes can be opened
    Arguments:
    boxes --> list of lists with keys
    return: true if all boxes can be opened else False"""
    n = len(boxes)
    opened = [False] * n
    opened[0] = True
    keys = set(boxes[0])
    while True:
        new_keys = False
        for i in range(n):
            if not opened[i] and i in keys:
                opened[i] = True
                keys.update(boxes[i])
                new_keys = True
        if not new_keys:
            break

    return all(opened)
