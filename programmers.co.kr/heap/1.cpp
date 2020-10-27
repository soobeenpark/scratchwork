// https://programmers.co.kr/learn/courses/30/lessons/42626
// Spicier

#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(),
                                                      scoville.end());
    int answer = 0;

    while (pq.size() >= 2 && pq.top() < K) {
        int least = pq.top();
        pq.pop();
        int secondLeast = pq.top();
        pq.pop();
        pq.push(least + 2 * secondLeast);
        answer++;
    }

    return pq.top() < K ? -1 : answer;
}
