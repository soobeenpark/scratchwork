# https://programmers.co.kr/learn/courses/30/lessons/42839
# Finding Primes

from itertools import permutations
from math import sqrt

def solution(numbers):
    # Build up all possible numbers from numbers string
    s = set()
    for length in range(1, len(numbers)+1):
        s |= set(int("".join(num)) for num in permutations(numbers, length))

    # Delete non-primes using Eratosthenes Sieve
    s -= set((0, 1))
    for i in range(2, int(sqrt(max(s)))+1):
        s -= set([composite for composite in range(i*2, max(s)+1, i)])

    # Return number of possible prime numbers
    return len(s)
