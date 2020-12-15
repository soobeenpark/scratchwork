#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int best = INT_MIN;
    int max_subarray_prev = 0;

    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;

        /*
        if (max_subarray_prev > 0) {
            max_subarray_prev += ai;
        } else {
            max_subarray_prev = ai;
        }
        */
        max_subarray_prev = max(ai, max_subarray_prev + ai);
        best = max(best, max_subarray_prev);
    }
    cout << best << endl;
}
