#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int,int> &m1, const pair<int,int> &m2) {
    if (m1.second == m2.second) {
        return m1.first < m2.first;
    } else {
        return m1.second < m2.second;
    }
}

int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> meetingTimes;
    meetingTimes.reserve(n);

    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        if (start <= end) {
            meetingTimes.push_back({start, end});
        }
    }

    sort(meetingTimes.begin(), meetingTimes.end(), compare);

    int nextEnd = 0;
    int ans = 0;
    for (pair<int,int> p : meetingTimes) {
        if (nextEnd <= p.first) {
            ans++;
            nextEnd = p.second;
        }
    }
    cout << ans << endl;
}
