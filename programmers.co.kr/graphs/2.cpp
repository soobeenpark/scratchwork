// https://programmers.co.kr/learn/courses/30/lessons/49191
// Rankings

#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    // Initialize matrix
    bool adj[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = false;
        }
    }
    for (vector<int> result : results) {
        adj[result[0]][result[1]] = true;
    }

    // Floyd Warshall algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (adj[i][k] && adj[k][j]) {
                    adj[i][j] = true;
                }
            }
        }
    }

    // Count number of people who have determinable results
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (adj[i][j] || adj[j][i]) {
                count++;
            }
        }
        ans += (count == n - 1);
    }
    return ans;
}
