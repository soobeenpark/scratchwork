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

Uses the naiive straightforward approach, to calculate the number of bit flips
necessary for each number using a bitwise XOR.
"""

import sys

def bitFlipsBitwise(n):
    """
    Naiive implementation of number of bit flips necessary in binary counting

    pre: n must be a positive integer (greater than 0).
    param (int): n
    return (list): Array containing the number of bit flips for each number, starting from 0.
    """
    ret = [0] * n
    i = 1
    while (i <= n):
        numBitFlips = bin(i ^ (i-1)).count("1")
        ret[i-1] = numBitFlips
        i += 1
    assert(0 not in ret)
    return ret

def main():
    if len(sys.argv) != 2 or int(sys.argv[1]) <= 0:
        print("Please enter a positive integer argument n")
        sys.exit(1)

    n = int(sys.argv[1])
    for idx, val in enumerate(bitFlipsBitwise(n)):
        print(idx + 1, ":\t", val)


if __name__ == '__main__':
    main()
