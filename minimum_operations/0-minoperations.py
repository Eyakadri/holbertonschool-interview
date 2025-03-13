#!/usr/bin/python3
""" Minimum Operations """


def minOperations(n):
    """ Minimum Operations """
    if not isinstance(n, int) or n < 2:
        return 0
    op = 0
    k = 3
    while n % 2 == 0:
        op += 2
        n = n//2
    while k <= n:
        while n % k == 0:
            op += k
            n = n//k
        k += 2
    return int(op)
