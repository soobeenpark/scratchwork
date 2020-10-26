// https://programmers.co.kr/learn/courses/30/lessons/42587
// Printer

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    queue<int> q;
    map<int, int> freq;

    // Init queue
    for (int i = 0; i < priorities.size(); ++i) {
        q.push(i);
        freq[priorities[i]]++;
    }

    map<int, int>::reverse_iterator riter = freq.rbegin();
    int numPrinted = 0;
    while (!q.empty()) {
        // Get maximum unprinted
        if (riter->second == 0) {
            riter++;
        }
        int maximum = riter->first;

        // Process front element
        if (priorities[q.front()] == maximum) {
            ++numPrinted;
            if (q.front() == location) {
                return numPrinted;
            }
            riter->second--;
        } else {
            q.push(q.front());
        }
        q.pop();
    }
}
