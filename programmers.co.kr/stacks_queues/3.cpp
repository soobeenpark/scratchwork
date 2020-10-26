// https://programmers.co.kr/learn/courses/30/lessons/42583
// Trucks Crossing a Bridge

#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    queue<int> q;
    int index = 0;
    int sum = 0;

    while (index != truck_weights.size()) {
        answer++;

        if (q.size() == bridge_length) {
            sum -= q.front();
            q.pop();
        }

        int next = truck_weights[index];
        if (sum + next <= weight) {
            q.push(next);
            sum += next;
            index++;
        } else {
            q.push(0);
        }
    }

    answer += bridge_length;

    return answer;
}
