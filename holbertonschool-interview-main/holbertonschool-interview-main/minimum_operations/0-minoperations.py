#!/usr/bin/python3
"""
Module for calculating the minimum number of
operations to achieve `n` H characters
in a file using only Copy All and Paste operations.
"""


def minOperations(n):
    """
    Calculate the minimum number of operations to achieve `n` H characters.

    Args:
        n (int): Target number of H characters.

    Returns:
        int: The minimum number of operations, or 0 if n is impossible.
    """
    if n <= 1:
        return 0

    operations = 0
    factor = 2

    # Factorize `n` to determine the sequence of operations
    while n > 1:
        while n % factor == 0:
            operations += factor
            n //= factor
        factor += 1

    return operations
