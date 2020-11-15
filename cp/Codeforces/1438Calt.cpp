// Solution uses the fact that if (node's value) == (node's position's parity)
// (ie. a node at position 6 must have an even value, and the node at position
// 7 must have an odd value), then the matrix is gauranteed to not have
// any adjacent nodes that are of equal value.
// Can think of it like coloring a chessboard, where the chessboard color
// (black/white) is the node's value's parity (even/odd).

#include <bits/stdc++.h>
using namespace std;

int matrix[100][100];
int n, m;

bool isValid(int row, int col) {
    return (row >= 0 && row < n) && (col >= 0 && col < m);
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
            }
        }

        // Change parity of values in each node
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                // equivalent to:
                // matrix[r][c] += ((r^c) % 2) != (matrix[r][c] % 2);
                matrix[r][c] += (r ^ c ^ matrix[r][c]) & 1;
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
