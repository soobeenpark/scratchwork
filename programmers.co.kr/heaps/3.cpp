// https://programmers.co.kr/learn/courses/30/lessons/42628
// Double Ended Priority Queue

#include <map>
#include <string>
#include <vector>

using namespace std;

void deleteElem(map<int, int> &depq, bool getMin) {
    if (depq.empty()) {
        return;
    }

    auto it = getMin ? depq.begin() : --depq.end();
    it->second--;
    if (it->second == 0) {
        depq.erase(it);
    }
}

vector<int> solution(vector<string> operations) {
    map<int, int> depq;

    for (string op : operations) {
        // Parse command
        char arg1 = op[0];
        int arg2 = stoi(op.substr(2));

        if (arg1 == 'I') {
            // Insert
            depq[arg2]++;
        } else {
            // Delete
            deleteElem(depq, arg2 == -1);
        }
    }

    vector<int> answer;
    if (depq.empty()) {
        answer.push_back(0);
        answer.push_back(0);
    } else {
        int max = depq.rbegin()->first;
        int min = depq.begin()->first;
        answer.push_back(max);
        answer.push_back(min);
    }
    return answer;
}
