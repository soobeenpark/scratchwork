#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, L;
    cin >> N >> L;

    set<int> leakPositions;
    // Step 1: Add n waterleak positions into balanced BST - O(nlogn)
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        leakPositions.insert(x);
    }

    // Step 2: Repeatedly put tape starting from leftmost pos - O(nlogn)
    int numTapes = 0;
    while (!leakPositions.empty()) {
        int lowest = *leakPositions.begin();
        leakPositions.erase(lowest);
        for (int i = 1; i < L; i++) {
            leakPositions.erase(lowest+i);
        }
        numTapes++;
    }

    cout << numTapes << endl;
}
