#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

auto cmp = [](pair<int,int> p1, pair<int,int> p2) {
    return p1.second < p2.second;
};

typedef priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> mypq;

bool scheduleTask(vector<int> &taskSchedule, const pair<int,int> &task) {
    int d = task.first;
    int w = task.second;

    for (int i = d-1; i >= 0; i--) {
        if (taskSchedule[i] == 0) {
            taskSchedule[i] = w;
            return true;
        }
    }
    return false;
}

int main() {
    // Read n
    int n;
    cin >> n;

    // Read in tasks
    mypq tasks(cmp);
    int latestDueDate = 0;
    for (int i = 0; i < n; i++) {
        int d, w;
        cin >> d >> w;
        tasks.push({d, w});
        latestDueDate = max(latestDueDate, d);
    }

    // Greedy algorithm:
    // Do each top task in the pq as close to the deadline as possible.
    // If not possible to schedule bc tasks already exist on same day, then drop the task.
    int numTasksCompleted = 0;
    vector<int> taskSchedule(latestDueDate, 0);
    while (!tasks.empty()) {
        pair<int,int> todo = tasks.top();
        tasks.pop();
        if (scheduleTask(taskSchedule, todo)) {
            numTasksCompleted++;
        }
    }

    // Sum weights of all tasks that have been scheduled.
    int ans = 0;
    for (int i = 0; i < latestDueDate; i++) {
        ans += taskSchedule[i];
    }
    cout << ans << endl;
}
