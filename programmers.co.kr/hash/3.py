# https://programmers.co.kr/learn/courses/30/lessons/42578


def solution(clothes):
    d = {}
    answer = 1
    for __, clothingType in clothes:
        d[clothingType] = d.get(clothingType, 0) + 1

    for clothingType in d.keys():
        answer *= (d[clothingType] + 1)
    answer -= 1
    return answer
