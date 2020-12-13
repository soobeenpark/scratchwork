#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int x;
        cin >> x;

        int pos = 0;
        int stride = 1;
        while (pos < x) {
            pos += stride;
            stride++;
        }

        if (x == pos - 1) {
            cout << stride << endl;
        } else {
            cout << stride-1 << endl;
        }
    }
}
