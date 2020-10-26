#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void updateProgress(vector<int> &progresses, vector<int> &speeds) {
    for (int i = 0; i < progresses.size(); i++) {
        if (progresses[i] < 100) {
            progresses[i] += speeds[i];
        }
    }
}

void checkAndDeploy(const vector<int> &progresses, queue<int> &q,
                    vector<int> &answer, int &nextToDeploy,
                    unordered_set<int> &finished) {
    int count = 0;
    for (int i = nextToDeploy; i < progresses.size(); i++) {
        if (progresses[i] >= 100 && finished.find(i) == finished.end()) {
            finished.insert(i);
            if (nextToDeploy == i) {
                // Deploy
                while (!q.empty()) {
                    nextToDeploy = max(nextToDeploy, q.front());
                    q.pop();
                    count++;
                }
                count++; // For the current job
                nextToDeploy++;
            } else {
                // Add to queue
                q.push(i);
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
        checkAndDeploy(progresses, q, answer, nextToDeploy, finished);
    }
    return answer;
}
