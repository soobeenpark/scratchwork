# https://programmers.co.kr/learn/courses/30/lessons/42748
# Kth Number

def solution(array, commands):
    return [sorted(array[a - 1:b])[c - 1] for a, b, c in commands]
