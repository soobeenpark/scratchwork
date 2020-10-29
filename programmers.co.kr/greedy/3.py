# https://programmers.co.kr/learn/courses/30/lessons/42860
# Joystick

NUM_CHARS = 26
BASE = ord('A')

def getCharDiff(char):
    '''Return how many joystick moves to change current char to A'''
    return min(ord(char) - BASE, (-1 * (ord(char) - BASE)) % NUM_CHARS)

def getNextInd(name, ind):
    '''Return next index to process in name'''
    left = 1
    right = 1
    while name[(ind+right)%len(name)] == 'A':
        right += 1
    while name[(ind-left)%len(name)] == 'A':
        left += 1

    if left < right:
        return (ind-left)%len(name)
    else:
        return (ind+right)%len(name)


def solution(name):
    ind = 0
    name = list(name)
    target = ['A'] * len(name)

    answer = getCharDiff(name[0])
    name[0] = 'A'

    while name != target:
        newInd = getNextInd(name, ind)
        answer += min((newInd - ind) % len(name), (ind - newInd) % len(name))
        ind = newInd

        # Fix current index
        answer += getCharDiff(name[ind])
        name[ind] = 'A'

    return answer
