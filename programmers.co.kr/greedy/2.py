# https://programmers.co.kr/learn/courses/30/lessons/42883
# Making Biggest Number

def solution(number, k) -> str:
    stack = []
    for numc in number:
        while stack and stack[-1] < numc and k > 0:
            stack.pop()
            k -= 1
        stack.append(numc)

    if (k > 0):
        stack = stack[:-k]

    return "".join(stack)
