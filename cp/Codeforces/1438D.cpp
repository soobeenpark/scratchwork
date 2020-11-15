#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int acc = 0;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr.push_back(x);
        acc ^= x;
    }

    // Impossible
    if (n % 2 == 0 && acc != 0) {
        cout << "NO" << endl;
        return 0;
    }

    // Possible
    cout << "YES" << endl;
    cout << n - 2 << endl;
    // sliding window of size 3, going forward
    for (int i = 1; i < n - 1; i += 2) {
        cout << i << " " << i + 1 << " " << i + 2 << endl;
    }
    // sliding window of size 3, going backward
    for (int i = n - 3 - (n % 2); i > 0; i -= 2) {
        cout << i << " " << i + 1 << " " << i + 2 << endl;
    }
}
