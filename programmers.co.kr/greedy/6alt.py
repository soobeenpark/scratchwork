# https://programmers.co.kr/learn/courses/30/lessons/42884
# Speeding Camera

def solution(routes):
    lastCamera = -30001
    routes.sort(key = lambda x: x[1])
    answer = 0

    for route in routes:
        if lastCamera < route[0]:
            answer += 1
            lastCamera = route[1]

    return answer

