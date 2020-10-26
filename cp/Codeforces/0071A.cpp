// 0071A. Way Too Long Words

#include <bits/stdc++.h>
using namespace std;

#define ar array
#define ll long long

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s.size() > 10) {
            s = s.substr(0, 1) + to_string(s.size() - 2) +
                s.substr(s.size() - 1, 1);
        }
        cout << s << "\n";
    }
}
