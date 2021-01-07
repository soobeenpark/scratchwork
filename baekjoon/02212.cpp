#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <iterator>

using namespace std;

const int MAX = 10000;
int n, k;

int main() {
    // Read in inputs
    cin >> n >> k;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    set<int> sensor_positions;
    for (int i = 0; i < n; i++) {
        int pos;
        cin >> pos;

        sensor_positions.insert(pos);
    }

    // Greedy algorithm:
    // Will allow k-1 gaps to go uncovered by sensor towers.
    // Thus, we only need n-k gaps to be covered by sensor towers.
    // (Gap is the distance between two adjacent sensors).

    // Store n-1 gap distances into priority queue
    priority_queue<int> gap_distances;
    for (set<int>::iterator it = sensor_positions.begin(); std::next(it,1) != sensor_positions.end(); it++) {
        int left = *it;
        int right = *std::next(it, 1);
        gap_distances.push(right - left);
    }

    // Discard k-1 of the largest gaps from pq
    while (!gap_distances.empty() && --k) {
        gap_distances.pop();
    }

    // Sum remaining gaps
    int ans = 0;
    while (!gap_distances.empty()) {
        ans += gap_distances.top();
        gap_distances.pop();
    }
    cout << ans << endl;
}
