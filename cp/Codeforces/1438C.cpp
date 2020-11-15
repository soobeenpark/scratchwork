// Solution goes through whole matrix, and on each "error" node it encounters,
// does a DFS on that node.
// Note that this only works under the assumption that a valid solution exists,
// which is stated in the problem.

#include <bits/stdc++.h>
using namespace std;

int matrix[100][100];
bool visited[100][100];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m;

void visit(int r, int c);
void unvisit(int r, int c);

bool isValid(int row, int col) {
    return (row >= 0 && row < n) && (col >= 0 && col < m);
}

// Does DFS on valid adjacent nodes
void dfsAdj(int r, int c) {
    for (int k = 0; k < 4; k++) {
        int xadj = c + dx[k];
        int yadj = r + dy[k];

        if (isValid(yadj, xadj) && matrix[r][c] == matrix[yadj][xadj]) {
            if (!visited[yadj][xadj]) {
                // dfs by incrementing
                visit(yadj, xadj);
            } else {
                // dfs by decrementing previously incremented value
                unvisit(yadj, xadj);
            }
        }
    }
}

// Increment and mark visited, then do dfs on adjacent nodes
void visit(int r, int c) {
    visited[r][c] = true;
    matrix[r][c]++;

    dfsAdj(r, c);
}

// Decrement and mark unvisited, then do dfs on adjacent nodes
void unvisit(int r, int c) {
    visited[r][c] = false;
    matrix[r][c]--;

    dfsAdj(r, c);
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m;

        // initialize matrices
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                cin >> matrix[r][c];
                visited[r][c] = false;
            }
        }

        // DFS
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                for (int k = 0; k < 4; k++) {
                    int xadj = c + dx[k];
                    int yadj = r + dy[k];

                    if (isValid(yadj, xadj) &&
                        matrix[r][c] == matrix[yadj][xadj]) {
                        if (!visited[r][c]) {
                            // dfs by incrementing
                            visit(r, c);
                        } else {
                            // dfs by decrementing previously incremented value
                            unvisit(r, c);
                        }
                    }
                }
            }
        }

        // print output
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                cout << matrix[r][c] << " ";
            }
            cout << endl;
        }
    }
}
