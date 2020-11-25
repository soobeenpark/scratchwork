#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int n; cin >> n;

        // Initialize vector passed in as argument
        vector<int> v(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        
        // Delete consecutive elements that are same, resize vector
        int nNew = unique(v.begin(), v.end()) - v.begin();
        v.resize(nNew);

        // Initialize counter vector where index is element in v (ai)
        vector<int> counter(n+1, 1);
        for (int i = 0; i < nNew; i++) {
            counter[v[i]]++;
        }
        counter[v[0]]--;
        counter[v[n-1]]--;

        // counter now holds the minimum num operation in the case where each
        // index is chosen as the x. The answer is the minimum count in counter.
        int minimum = INT_MAX;
        for (int i = 0; i < nNew; i++) {
            minimum = min(minimum, counter[v[i]]);
        }
        cout << minimum << endl;
    }
}
