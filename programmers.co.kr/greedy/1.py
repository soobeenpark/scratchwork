# https://programmers.co.kr/learn/courses/30/lessons/42862
# Gym Clothes

def solution(n, lost, reserve):
    ans = set()
    lostCopy = [l for l in lost if l not in reserve]
    reserve = [r for r in reserve if r not in lost]
    lost = lostCopy

    # Go in order asking for pair of extra clothes from neighbor
    for lostPerson in lost.copy():
        if (lostPerson-1) in reserve:
            lost.remove(lostPerson)
            reserve.remove(lostPerson-1)
        elif (lostPerson+1) in reserve:
            lost.remove(lostPerson)
            reserve.remove(lostPerson+1)
    return n - len(lost)
