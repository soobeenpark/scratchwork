# https://programmers.co.kr/learn/courses/30/lessons/42885
# Life Boat

def solution(people, limit):
    people.sort()
    light = 0
    heavy = len(people) - 1
    count = 0

    while light <= heavy:
        if people[light] + people[heavy] <= limit:
            light += 1
        heavy -= 1
        count += 1
    return count
