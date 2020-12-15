#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;

int n;
int stickers[2][MAX];
// stores maximum of all stickers from each column to everything on its right
int dp[MAX][3];

int search(int col, int status) {
    // if status = 0, no sticker in prev row was ripped
    // if status = 1, upper sticker in prev row was ripped
    // if status = 2, bottom sticker in prev row was ripped

    if (col == n) {
        return 0;
    }

    // check cached result
    if (dp[col][status] != -1) {
        return dp[col][status];
    }

    int ans = search(col + 1, 0);
    if (status != 1) {
        // rip top sticker on current row
        ans = max(ans, search(col + 1, 1) + stickers[0][col]);
    }
    if (status != 2) {
        // rip bottom sticker on current row
        ans = max(ans, search(col + 1, 2) + stickers[1][col]);
    }

    // set dp cache
    dp[col][status] = ans;
    return ans;
}

void test_case() {
    cin >> n;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> stickers[i][j];
        }
    }

    // initialize dp array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = -1;
        }
    }

    cout << search(0, 0) << endl;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        test_case();
    }
}
