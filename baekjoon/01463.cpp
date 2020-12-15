#include <bits/stdc++.h>
using namespace std;

vector<int> dp;
int X;

int search(int x) {
    // base case
    if (x < 1) {
        return INT_MAX;
    } else if (x == 1) {
        return 0;
    }

    // check dp cache
    if (dp[x] != -1) {
        return dp[x];
    }

    int ans = INT_MAX;
    ans = min(ans, search(x - 1) + 1);
    if (x % 3 == 0) {
        ans = min(ans, search(x / 3) + 1);
    }
    if (x % 2 == 0) {
        ans = min(ans, search(x / 2) + 1);
    }
    dp[x] = ans;
    return ans;
}

int main() {
    cin >> X;
    dp = vector<int>(X + 1, -1);

    cout << search(X) << endl;
}
