# https://programmers.co.kr/learn/courses/30/lessons/42840
# Mock Exam


def solution(answers):
    patterns = [[1, 2, 3, 4, 5],
                [2, 1, 2, 3, 2, 4, 2, 5],
                [3, 3, 1, 1, 2, 2, 4, 4, 5, 5]]

    scores = [0] * 3
    for i, answer in enumerate(answers):
        for personId, pattern in enumerate(patterns):
            scores[personId] += int(answer == pattern[i % len(pattern)])

    return [
        personId + 1 for personId,
        score in enumerate(scores) if score == max(scores)]
