#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    int maxDays = 0;
    vector<int> answer;

    for (int i = 0; i < progresses.size(); i++) {
        int days = ((99 - progresses[i]) / speeds[i]) + 1;

        if (answer.empty() || maxDays < days) {
            // Takes longer than previous jobs
            answer.push_back(1);
        } else {
            // This job was already finished and ready for deployment
            ++answer.back();
        }

        maxDays = max(maxDays, days);
    }
    return answer;
}
