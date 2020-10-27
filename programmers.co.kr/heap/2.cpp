// https://programmers.co.kr/learn/courses/30/lessons/42627
// Disk Controller

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> jobs) {

    sort(jobs.begin(), jobs.end(),
         [](const vector<int> &a, const vector<int> &b) -> bool {
             return a[0] > b[0];
         });

    int time = 0;
    int numJobs = jobs.size();
    int answer = 0;
    bool busy = false;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pair<int, int> curr;

    while (!(jobs.empty() && pq.empty() && !busy)) {
        // Insert jobs started at current time
        while (!jobs.empty() && jobs.back()[0] == time) {
            vector<int> job = jobs.back();
            jobs.pop_back();
            pq.push(make_pair(job[1], job[0]));
        }

        // Check if current job finished
        if (busy && curr.first == time) {
            answer += curr.first - curr.second;
            busy = false;
        }

        // Start new job
        if (!busy && !pq.empty()) {
            curr = pq.top();
            curr.first += time; // Change to when job will finish
            pq.pop();
            busy = true;
        }
        time++;
    }

    return answer / numJobs;
}
