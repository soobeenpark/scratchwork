# https://programmers.co.kr/learn/courses/30/lessons/42839
# Finding Primes

from math import floor, sqrt

class Searcher:
    seen = set()

    def __init__(self, numbers):
        self.numbers = numbers

    def search(self, builder, level):
        if (level == len(self.numbers)):
            if not builder or int(builder) in self.seen:
                return 0
            self.seen.add(int(builder))
            return int(isPrime(int(builder)))

        else:
            # Generate subset excluding current number
            count = self.search(builder, level+1)
            # Generate subset including current number, all permutations
            for i in range(len(builder)+1):
                builderPermute = builder[0:i] + self.numbers[level] + builder[i:len(builder)]
                count += self.search(builderPermute, level+1)
            return count


def isPrime(num):
    '''precondition: nums is a nonnegative integer.'''
    if (num == 2):
        return True
    elif (num == 0 or num == 1 or num % 2 == 0):
        return False

    for i in range(3, floor(sqrt(num))+1, 2):
        if (num % i == 0):
            return False
    return True


def solution(numbers):
    s = Searcher(numbers)
    return s.search("", 0)
