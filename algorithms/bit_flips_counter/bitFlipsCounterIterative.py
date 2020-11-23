"""
Uses an iterative method to fill out the result list.
"""

import sys

def bitFlipsIterative(n):
    """
    Iterative implementation of number of bit flips necessary in binary counting

    pre: n must be a positive integer (greater than 0).
    param (int): n
    return (list): Array containing the number of bit flips for each number, starting from 1.
    """
    ret = [0] * n
    ret[0] = 1
    binSize = 1
    while (binSize < n*2):
        i = 1
        # Copy second half from first half
        while (i + binSize // 2 <= n and i <= binSize // 2):
            ret[i + binSize // 2 - 1] = ret[i - 1] 
            # Last element is special - incremented by one
            if (i == binSize // 2):
                ret[i + binSize // 2 - 1] += 1
            i += 1
        binSize *= 2
    return ret


def main():
    if len(sys.argv) != 2 or int(sys.argv[1]) <= 0:
        print("Please enter a positive integer argument n")
        sys.exit(1)

    n = int(sys.argv[1])
    for idx, val in enumerate(bitFlipsIterative(n)):
        print(idx+1, ":\t", val)

if __name__ == '__main__':
    main()
