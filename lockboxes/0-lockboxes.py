#!/usr/bin/python3
def canUnlockAll(boxes):
    """checks if all boxes can be opened """
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
