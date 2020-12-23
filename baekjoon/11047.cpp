#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int cointypes[n];

    // store cointypes in descending order
    for (int i = n-1; i >= 0; i--) {
        cin >> cointypes[i];
    }

    // greedy approach
    int ans = 0;
    for (int i = 0; k > 0 && i < n; i++) {
        int numCoins = k / cointypes[i];
        ans += numCoins;
        k = k % cointypes[i];
    }
    cout << ans << endl;
}
