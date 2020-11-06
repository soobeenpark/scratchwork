#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

typedef long long ll;

int getMinInd(vector<int> timeLeft) {
    auto it = min_element(timeLeft.begin(), timeLeft.end());
    assert(*it >= 0);
    return distance(timeLeft.begin(), it);
}

void updateTimes(vector<int> &timeLeft, int timeToElapse) {
    for_each(timeLeft.begin(), timeLeft.end(), 
            [&timeToElapse](int &t) { t -= timeToElapse; }
    );
}

ll solution(int n, vector<int> times) {
    vector<int> timeLeft(times.size(), 0);
    ll answer = 0;
    while (n > 0) {
        // Get earliest next person who will finish processing 
        int i = getMinInd(timeLeft);
        answer += timeLeft[i];

        // Assume the next person got processed - need to elapse time for rest
        updateTimes(timeLeft, timeLeft[i]);

        // Add new person
        timeLeft[i] = times[i];
        
        // Deque person in line
        n--;
       
        cout << "time " << answer << ": ";
        for (int x : timeLeft) {
            cout << x << " ";
        }
        cout << endl;
    }

    // Add any remaining people in line not finished yet
    answer += *max_element(timeLeft.begin(), timeLeft.end());
    return answer;
}

int main() {
    vector<int> times({7, 10});
    cout << solution(6, times) << endl;
}
