#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 50;
int n;
char board[MAX][MAX];

int countLongest() {
    // count longest in row
    int longestInRow = 1;
    for (int i = 0; i < n; i++) {
        int rowConsecutive = 1;
        for (int j = 1; j < n; j++) {
            if (board[i][j] == board[i][j-1]) {
                rowConsecutive++;
            } else {
                longestInRow = max(longestInRow, rowConsecutive);
                rowConsecutive = 1;
            }
        }
        longestInRow = max(longestInRow, rowConsecutive);
    }

    // count longest in col
    int longestInCol = 1;
    for (int j = 0; j < n; j++) {
        int colConsecutive = 1;
        for (int i = 1; i < n; i++) {
            if (board[i][j] == board[i-1][j]) {
                colConsecutive++;
            } else {
                longestInCol = max(longestInCol, colConsecutive);
                colConsecutive = 1;
            }
        }
        longestInCol = max(longestInCol, colConsecutive);
    }

    return max(longestInRow, longestInCol);
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != n-1 && board[i][j] != board[i][j+1]) {
                // swap curr with right
                std::swap(board[i][j], board[i][j+1]);

                ans = max(ans, countLongest());

                // swap back
                std::swap(board[i][j], board[i][j+1]);
            }

            if (i != n-1 && board[i][j] != board[i+1][j]) {
                // swap curr with below
                std::swap(board[i][j], board[i+1][j]);

                ans = max(ans, countLongest());

                // swap back
                std::swap(board[i][j], board[i+1][j]);
            }
        }
    }
    
    cout << ans << endl;
}
