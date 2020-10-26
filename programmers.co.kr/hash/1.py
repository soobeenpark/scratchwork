# https://programmers.co.kr/learn/courses/30/lessons/42576?language=python3
# Unfinished Marathoner

import collections


def solution(participant, completion):
    a = collections.Counter(participant) - collections.Counter(completion)
    answer = list(a.keys())[0]

    return answer
