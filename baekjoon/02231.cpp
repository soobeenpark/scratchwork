#include <bits/stdc++.h>
using namespace std;

int createM(int N) {
    int M = N;
    while (N > 0) {
        M += N % 10;
        N /= 10;
    }
    return M;
}

int main() {
    int target;
    cin >> target;

    for (int i = 1; i <= 1000000; i++) {
        int M = createM(i);
        if (target == M) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
