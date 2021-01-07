#include <bits/stdc++.h>
using namespace std;

bool findTastiestGrass(const pair<int, int> &p1, const pair<int, int> &p2) {
    return p1.second < p2.second;
}

int main() {
    // Step 1 - Initialize the trail and other variables
    int L, N, rf, rb;
    cin >> L >> N >> rf >> rb;
    map<int, int> trail;
    for (int i = 0; i < N; i++) {
        int xi, ci;
        cin >> xi >> ci;
        trail.insert({xi, ci});
    }

    // Step 2 - Greedy algorithm:
    // Always find next patch of grass which is tastiest
    map<int, int>::iterator it = max_element(trail.begin(), trail.end(), findTastiestGrass); 
    int prevPos = 0;
    long long ans = 0;
    while (it != trail.end()) {
        // Eat grass
        int tastiestTaste = it->second;
        int pos = it->first;
        ans += (rf - rb) * (long long)tastiestTaste * (pos - prevPos);

        // Update values
        prevPos = pos;
        it = max_element(next(it, 1), trail.end(), findTastiestGrass);
    }
    cout << ans << endl;
}
