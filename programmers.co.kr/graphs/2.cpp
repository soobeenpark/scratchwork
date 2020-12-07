#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    // Initialize matrix
    bool adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = false;
        }
    }
    for (vector<int> result : results) {
        adj[result[0]][result[1]] = true;
    }

    // Floyd Warshall algorithm
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

            }
        }
    }

    // Count number of people who have determinable results
}
