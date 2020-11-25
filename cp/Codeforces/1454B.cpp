#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;

    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        map<int, int> s;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            s[ai]++;
            v.push_back(ai);
        }
        int uniqueNum = -1;
        auto it = s.begin();
        for (; it != s.end(); it++) {
            if (it->second == 1) {
                uniqueNum = it->first;
                break;
            }
        }
        if (uniqueNum == -1) {
            cout << uniqueNum;
        } else {
            cout << distance(v.begin(), find(v.begin(), v.end(), uniqueNum)) + 1;
        }
        cout << endl;
    }
}
