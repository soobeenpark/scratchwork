// Uses DP bottom-up approach iteratively, instead of top-down recursive.

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;
int n;
int stickers[2][MAX];
int dp[MAX][3];

void test_case() {
    cin >> n;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> stickers[i][j];
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i+1][0] = max(dp[i + 1][0], max(dp[i][0], max(dp[i][1], dp[i][2])));
        // rip off top sticker of ith row
        dp[i+1][1] = max(dp[i + 1][1],
                           max(dp[i][0], dp[i][2]) + stickers[1][i]);
        // rip off bottom sticker of ith row
        dp[i+1][2] = max(dp[i + 1][2],
                           max(dp[i][0], dp[i][1]) + stickers[0][i]);
    }

    int ans = max(dp[n][0], max(dp[n][1], dp[n][2]));
    cout << ans << endl;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        test_case();
    }
}
