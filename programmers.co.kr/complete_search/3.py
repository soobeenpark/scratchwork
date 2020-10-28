# https://programmers.co.kr/learn/courses/30/lessons/42842
# Carpet

from math import sqrt

def solution(brown, yellow):
    total = brown + yellow
    for h in range(3, int(sqrt(total))+1):
        if (total % h == 0):
            w = total / h
            if ((w-2) * (h-2) == yellow):
                return [w, h]
