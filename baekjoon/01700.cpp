#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int n, k;

// Remove one device from plugged - the one that will be used later than all others
void unplugDevice(int sequence[], int curr, unordered_set<int>& plugged) {
    int dist = 0;
    int deviceToRemove = -1;
    for (unordered_set<int>::iterator it = plugged.begin(); it != plugged.end(); it++) {
        int device = *it;
        int scannedDist = distance(sequence+curr, find(sequence+curr, sequence+k, device));
        if (scannedDist > dist) {
            dist = scannedDist;
            deviceToRemove = device;
        }
    }
    assert(deviceToRemove > 0);
    plugged.erase(deviceToRemove);
}

int main() {
    cin >> n >> k;

    // Init sequence array
    int sequence[k];
    for (int i = 0; i < k; i++) {
        cin >> sequence[i];
    }

    // Go through sequence one by one
    unordered_set<int> plugged;
    int ans = 0;
    for (int i = 0; i < k; i++) {
        if (plugged.count(sequence[i])) {
            continue;
        }
        if ((int)plugged.size() == n) {
            ans++;
            unplugDevice(sequence, i, plugged);
        }
        plugged.insert(sequence[i]);
    }
    cout << ans << endl;
}
