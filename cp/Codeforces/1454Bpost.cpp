#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    
    while (T--) {
        int n; cin >> n;
        
        vector<int> idx(n+1, 0);
        vector<int> count(n+1, 0);

        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            idx[ai] = i + 1;  // Don't care if we overwrite idx at previous same ai value
            ++count[ai];
        }

        bool found = false;
        for (int i = 1; !found && i <= n; i++) {
            if (count[i] == 1) {
                cout << idx[i] << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << -1 << endl;
        }
    }
}
