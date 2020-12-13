#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t, k, d;
    cin >> n >> t >> k >> d;

    int time1 = t*((n-1)/k + 1);
    
    int cookiesDuringOvenBuild = d*k/t;
    int numBatchesLeft = (n-cookiesDuringOvenBuild - 1)/k + 1;
    int time2;
    if (numBatchesLeft % 2 == 0) {
        // finish with new second oven
        time2 = d + numBatchesLeft * t / 2;
    } else {
        // finish with original first oven
        time2 = (d/t)*t + (numBatchesLeft+1) * t /2;
    }
    string output = (time2 < time1) ? "YES" : "NO";
    cout << output << endl;
}
