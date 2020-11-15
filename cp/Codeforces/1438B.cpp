#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--) {
        set<int> seen;
        int sz;
        cin >> sz;
        int x;
        for (int i = 0; i < sz; i++) {
            cin >> x;
            seen.insert(x);
        }
        string msg = seen.size() == sz ? "NO" : "YES";
        cout << msg << endl;
    }
}
