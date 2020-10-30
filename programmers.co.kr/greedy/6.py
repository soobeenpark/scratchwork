# https://programmers.co.kr/learn/courses/30/lessons/42884
# Speeding Camera

def solution(routes):
    routes.sort(key = lambda x: x[1]) # Sort by exit times
    marked = [False] * len(routes)
    answer = 0

    while False in marked:
        # Get next car to mark
        for i, car in enumerate(routes):
            if not marked[i]:
                toMark = car
                break

        # Mark rest of cars that coincide
        for i, car in enumerate(routes):
            if toMark[1] in range(car[0], car[1]+1):
                marked[i] = True
        
        answer += 1
    return answer
