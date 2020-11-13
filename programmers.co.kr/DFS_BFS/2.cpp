// https://programmers.co.kr/learn/courses/30/lessons/43162
// Number Of Computer Networks

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<bool> visited;
vector<vector<int>> computers;
int n;

void BFS(int startNode) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (computers[node][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int solution(int _n, vector<vector<int>> _computers) {
    n = _n;
    computers = _computers;
    visited = vector<bool>(n, false);

    int answer = 0;
    auto it = find(visited.begin(), visited.end(), false);
    while (it != visited.end()) {
        BFS(distance(visited.begin(), it));
        answer++;
        it = find(visited.begin(), visited.end(), false);
    }
    return answer;
}
