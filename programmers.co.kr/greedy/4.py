# https://programmers.co.kr/learn/courses/30/lessons/42885
# Life Boat

from collections import deque

BOAT_SIZE = 2

def solution(people, limit):
    deq = deque(sorted(people))
    boat = []
    answer = 0

    while deq:
        # Get as many heavy people that will fit first
        while deq and len(boat) < BOAT_SIZE and deq[-1] + sum(boat) <= limit:
            boat.append(deq.pop())

        # See if there are remaining spots on the boat that can fit small person
        while deq and len(boat) < BOAT_SIZE and deq[0] + sum(boat) <= limit:
            boat.append(deq.popleft())

        # Clear boat
        boat = []
        answer += 1

    return answer
