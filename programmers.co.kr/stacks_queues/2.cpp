// https://programmers.co.kr/learn/courses/30/lessons/42586
// Deploying a Feature

#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool contains(int item, unordered_set<int> set) {
    return (set.find(item) != set.end());
}

void updateProgress(vector<int> &progresses, vector<int> &speeds) {
    for (int i = 0; i < progresses.size(); i++) {
        if (progresses[i] < 100) {
            progresses[i] += speeds[i];
        }
    }
}

void checkAndDeploy(const vector<int> &progresses, vector<int> &answer,
                    int &nextToDeploy, unordered_set<int> &finished) {
    int count = 0;
    for (int i = 0; i < progresses.size(); i++) {
        if (progresses[i] >= 100 && !contains(i, finished)) {
            finished.insert(i);
            if (i == nextToDeploy) {
                count++;
                nextToDeploy++;
                while (contains(nextToDeploy, finished)) {
                    count++;
                    nextToDeploy++;
                }
            }
        }
    }
    if (count != 0) {
        answer.push_back(count);
    }
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    queue<int> q;
    vector<int> answer;
    unordered_set<int> finished;
    int nextToDeploy = 0;

    while (nextToDeploy != progresses.size()) {
        // One iteration is one day
        updateProgress(progresses, speeds);

        // Check for finished jobs and deploy as necessary
        checkAndDeploy(progresses, answer, nextToDeploy, finished);
    }
    return answer;
}
