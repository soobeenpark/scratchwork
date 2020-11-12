// https://programmers.co.kr/learn/courses/30/lessons/42895
// Represent With N

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

const int THRESH = 9;
vector<unordered_set<int>> dp;

void applyAllOpps(unordered_set<int> &s, const unordered_set<int> &setA,
                  const unordered_set<int> &setB) {
    for (auto itA = setA.begin(); itA != setA.end(); itA++) {
        for (auto itB = setB.begin(); itB != setB.end(); itB++) {
            int a = *itA;
            int b = *itB;
            if (b != 0) {
                s.insert(a * b);
                s.insert(a / b);
                s.insert(a - b);
                s.insert(a + b);
            }
        }
    }
}

void generateValues(unordered_set<int> &s, int i, int N) {
    int NRepeatediTimes = 0;
    for (int j = 0; j < i; j++) {
        NRepeatediTimes *= 10;
        NRepeatediTimes += N;
    }
    s.insert(NRepeatediTimes);

    for (int j = 1; j < i; j++) {
        applyAllOpps(s, dp[j], dp[i - j]);
    }
}

int solution(int N, int number) {
    dp = vector<unordered_set<int>>(THRESH);
    dp[0] = {};

    for (int i = 1; i < THRESH; i++) {
        unordered_set<int> s;
        generateValues(s, i, N);
        if (find(s.begin(), s.end(), number) != s.end()) {
            return i;
        }
        dp[i] = s;
    }
    return -1;
}
