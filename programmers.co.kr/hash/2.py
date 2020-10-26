# https://programmers.co.kr/learn/courses/30/lessons/42577?language=python3

import itertools


def solution(phone_book):
    for i, __ in enumerate(phone_book):
        for j, num in enumerate(phone_book):
            if i != j and phone_book[i].startswith(phone_book[j]):
                return False

    return True
