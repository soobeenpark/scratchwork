// https://programmers.co.kr/learn/courses/30/lessons/42627
// Disk Controller

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> jobs) {
    // Sort by time each job takes, in increasing order
    sort(jobs.begin(), jobs.end(),
         [](vector<int> a, vector<int> b) -> bool { return a[1] < b[1]; });

    int elapsedSum = 0;
    int currTime = 0;
    int numJobs = jobs.size();

    while (!jobs.empty()) {
        for (int i = 0; i < jobs.size(); i++) {
            // Process first available shortest job
            if (jobs[i][0] <= currTime) {
                currTime += jobs[i][1];
                elapsedSum += currTime - jobs[i][0];
                jobs.erase(jobs.begin() + i);
                break;
            }

            // If no jobs to process, advance timestep by 1
            if (i == jobs.size() - 1) {
                currTime++;
            }
        }
    }
    return elapsedSum / numJobs;
}
