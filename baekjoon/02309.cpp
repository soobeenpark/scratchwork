#include <bits/stdc++.h>
using namespace std;

const int NUM_DWARFS = 9;

int main() {
    int heights[NUM_DWARFS];
    int sum = 0;

    for (int i = 0; i < NUM_DWARFS; i++) {
        cin >> heights[i];
        sum += heights[i];
    }

    sort(heights, heights + NUM_DWARFS);

    int not1, not2;
    bool found = false;
    for (int i = 0; !found && i < NUM_DWARFS - 1; i++) {
        for (int j = i + 1; !found && j < NUM_DWARFS; j++) {
            if (sum - (heights[i] + heights[j]) == 100) {
                not1 = i;
                not2 = j;
                found = true;
            }
        }
    }

    for (int i = 0; i < NUM_DWARFS; i++) {
        if (i != not1 && i != not2) {
            cout << heights[i] << endl;
        }
    }
}
