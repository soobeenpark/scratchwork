// Uses DP bottom-up approach iteratively, instead of top-down recursive.

#include <bits/stdc++.h>
using namespace std;

vector<int> dp;
int x;

int main() {
    cin >> x;
    dp = vector<int>(x + 1, INT_MAX);
    dp[1] = 0;

    for (int i = 1; i < x; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + 1);
        if (i * 2 <= x) {
            dp[i * 2] = min(dp[i * 2], dp[i] + 1);
        }
        if (i * 3 <= x) {
            dp[i * 3] = min(dp[i * 3], dp[i] + 1);
        }
    }

    cout << dp[x] << endl;
}
