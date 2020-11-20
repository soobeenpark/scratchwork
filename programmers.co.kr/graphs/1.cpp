// https://programmers.co.kr/learn/courses/30/lessons/49189
// Farthest Node

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int START = 1;

int bfs(int n, vector<int> adj[]) {
    queue<pair<int, int>> q; // <node, distance>
    q.push(make_pair(START, 0));
    vector<bool> visited(n + 1, false);
    visited[START] = true;
    vector<int> distances(n + 1, 0);
    int distance = 0;

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int node = p.first;
        distance = p.second;
        distances[node] = distance;

        for (int adjNode : adj[node]) {
            if (!visited[adjNode]) {
                visited[adjNode] = true;
                q.push(make_pair(adjNode, distance + 1));
            }
        }
    }
    // when we reach here, distance will always be max distance reachable by bfs
    int count = 0;
    for (int d : distances) {
        count += (d == distance);
    }
    return count;
}

int solution(int n, vector<vector<int>> edges) {
    // Create adjacency list
    vector<int> adj[n + 1];
    for (vector<int> edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    // bfs
    return bfs(n, adj);
}
