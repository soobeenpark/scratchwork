#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, p, v;
    int caseNum = 1;
    while (cin >> l >> p >> v) {
        if (l + p + v == 0) {
            return 0;  // Exit cond
        }
        int ans = 0;
        while (v > 0) {
            ans += min(v, l);
            v -= p;
        }

        cout << "Case " << caseNum++ << ": " << ans << endl;
    }

}
