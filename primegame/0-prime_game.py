#!/usr/bin/python3
"""
Prime Game module
"""


def isWinner(x, nums):
    """
    Determine the winner of the prime game.

    Maria and Ben play a game where they take turns choosing a prime number
    from a set of consecutive integers starting from 1 up to n, and removing
    that number and all its multiples from the set. The player who cannot
    make a move loses.

    Args:
        x (int): Number of rounds
        nums (list): Array of n values for each round

    Returns:
        str: Name of the player that won the most rounds ("Maria" or "Ben")
        None: If the winner cannot be determined
    """
    if not nums or x <= 0:
        return None

    max_n = max(nums)

    # Use Sieve of Eratosthenes to find all primes up to max_n
    is_prime = [True] * (max_n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, int(max_n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, max_n + 1, i):
                is_prime[j] = False

    # Count primes up to each number (cumulative count)
    prime_count = [0] * (max_n + 1)
    for i in range(1, max_n + 1):
        prime_count[i] = prime_count[i - 1] + (1 if is_prime[i] else 0)

    maria_wins = 0
    ben_wins = 0

    for n in nums:
        # If the number of primes is odd, Maria wins (she goes first)
        # If the number of primes is even, Ben wins
        if prime_count[n] % 2 == 1:
            maria_wins += 1
        else:
            ben_wins += 1

    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    else:
        return None
