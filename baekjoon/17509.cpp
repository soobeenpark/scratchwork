#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> times;

    int D, V;
    int totalErrors = 0;
    while (cin >> D >> V) {
        times.push_back(D);
        totalErrors += V;
    }

    sort(times.begin(), times.end());

    int clock = 0;
    int totalTime = 0;
    for (size_t i = 0; i < times.size(); i++) {
        clock += times[i];
        totalTime += clock;
    }

    cout << totalTime + 20 * totalErrors << endl;
}
