"""
This program outputs the number of bit flips necessary to convert a number N from
N-1.

For example, 11 (0b1011) to 12 (0b1100) requires flipping 3 bits.

For a given number n, the list of required bit flips from each of its previous number is printed.
For example, given n=12, the following would be printed.

1: 1
2: 2
3: 1
4: 3
5: 1
6: 2
7: 1
8: 4
9: 1
10: 2
11: 1
12: 3

Uses recursion to divide list in half. First, fills out the first half of the list.
Then, uses the first half to fill out the second half of the list.
"""

import sys

def isPowerOfTwo(n):
    """
    Returns true if n is a power of two
    """
    return (n != 0) and ((n & (n - 1)) == 0)


def getClosestPowerOfTwo(n):
    """
    Returns the nearest power of two that is greater than or equal to n
    """
    while (not isPowerOfTwo(n)):
        n = n + 1
    return n


def bitFlipsRecursive(n):
    """
    Recursive implementation of number of bit flips necessary in binary counting

    pre: n must be a positive integer (greater than 0).
    param (int): n
    return (list): Array containing the number of bit flips for each number, starting from 0.
    """
    if (n == 1):  # Base case
        return [1]

    powerOfTwo = getClosestPowerOfTwo(n)

    # Fill out first half of list
    ret = bitFlipsRecursive(powerOfTwo // 2)

    # Fill out second half of list
    i = powerOfTwo // 2 + 1
    while (i <= n):
        # Second half of array is a copy of the first half of the array, with
        # the exception of the very last value (copy of last element in first half + 1).
        numToAdd = ret[i - powerOfTwo // 2 - 1]
        if (i == n and isPowerOfTwo(n)):
            numToAdd += 1
        ret.append(numToAdd)
        i += 1
    return ret


def main():
    if len(sys.argv) != 2 or int(sys.argv[1]) <= 0:
        print("Please enter a positive integer argument n")
        sys.exit(1)

    n = int(sys.argv[1])
    for idx, val in enumerate(bitFlipsRecursive(n)):
        print(idx + 1, ":\t", val)


if __name__ == '__main__':
    main()
