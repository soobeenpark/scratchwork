# https://programmers.co.kr/learn/courses/30/lessons/42579?language=python3
# Best Album

import heapq


def solution(genres, plays):
    answer = []
    genreHeaps = {}
    genreTotals = {}
    for i, genre in enumerate(genres):
        # First add to genreHeaps
        genreHeap = genreHeaps.get(genre, [])
        heapq.heappush(genreHeap, (-plays[i], i))
        genreHeaps[genre] = genreHeap

        # Next add to genreTotals
        genreTotals[genre] = genreTotals.get(genre, 0) + plays[i]

    for genre, __ in sorted(
            genreTotals.items(), key=lambda x: x[1], reverse=True):
        genreHeap = genreHeaps[genre]
        for i in range(0, min(2, len(genreHeap))):
            # mostPlayed[0] is -numPlays, mostPlayed[1] is corresponding index
            # in original array
            mostPlayed = heapq.heappop(genreHeap)
            answer.append(mostPlayed[1])
    return answer
