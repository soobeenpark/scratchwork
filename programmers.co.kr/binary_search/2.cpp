// https://programmers.co.kr/learn/courses/30/lessons/43236
// Stepping Stones

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

int getCountToRemove(int distance, vector<int> rocks, int guess) {
    int count = 0;
    int prev = 0;
    for (int i = 0; i < rocks.size(); i++) {
        int curr = rocks[i];
        if (curr - prev < guess) {
            count++;
        } else {
            prev = curr;
        }
    }
    // Get last distance too
    if (distance - prev < guess) {
        count++;
    }
    return count;
}

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    int left = 0;
    int right = distance;
    sort(rocks.begin(), rocks.end());

    while (left < right) {
        int guess = left + (right - left) / 2;
        int count = getCountToRemove(distance, rocks, guess);

        if (count <= n) {
            answer = guess;
            left = guess + 1;
        } else {
            right = guess;
        }
    }
    assert(left == right);
    return answer;
}
