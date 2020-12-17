#include <climits>
#include <iostream>

using namespace std;

const int MAX = 50;
int n, m;
int board[MAX][MAX];

int find_min_ij(int i, int j) {
    int num_repaints = 0;
    for (int row = i; row < i + 8; row++) {
        for (int col = j; col < j + 8; col++) {
            num_repaints += (row ^ col ^ board[row][col]) & 1;
        }
    }

    return min(num_repaints, 64-num_repaints);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            board[i][j] = (c == 'W'); // 1 is W, 0 is B
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i <= n - 8; i++) {
        for (int j = 0; j <= m - 8; j++) {
            ans = min(ans, find_min_ij(i, j));
        }
    }
    cout << ans << endl;
}
