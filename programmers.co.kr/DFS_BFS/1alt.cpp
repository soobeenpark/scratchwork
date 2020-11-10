// https://programmers.co.kr/learn/courses/30/lessons/43165
// Target Number
// Includes a couple of different variations to solve the same problem.

#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Recursive search using bit manipulation (saves memory)
int solution_bits(vector<int> numbers, int target) {
    int answer = 0;
    int size = numbers.size();

    // Go through each leaf node in search graph
    for (int i = 0; i < (1 << size); i++) {
        int sum = 0;
        // Check each element in set
        for (int j = 0; j < size; j++) {
            // Convention: 1 - addition, 0 - subtraction
            if (i & (1 << j)) {
                sum += numbers[j];
            } else {
                sum -= numbers[j];
            }
        }
        answer += (sum == target);
    }
    return answer;
}

// DFS using stack
int solution_dfs(vector<int> numbers, int target) {
    stack<pair<int, int>> st;
    st.push(make_pair(0, 0));

    int answer = 0;
    while (!st.empty()) {
        pair<int, int> state = st.top();
        st.pop();

        if (state.second == numbers.size()) {
            answer += (state.first == target);
        } else {
            // Addition case
            int newSum = state.first + numbers[state.second];
            int newState = state.second + 1;
            st.push(make_pair(newSum, newState));

            // Subtraction case
            newSum = state.first - numbers[state.second];
            st.push(make_pair(newSum, newState));
        }
    }
    return answer;
}

// BFS using queue
int solution_bfs(vector<int> numbers, int target) {
    queue<pair<int, int>> q; // <sum, level>
    q.push(make_pair(0, 0));

    int answer = 0;
    while (!q.empty()) {
        pair<int, int> state = q.front();
        q.pop();

        if (state.second == numbers.size()) {
            answer += (state.first == target);
        } else {
            // Addition case
            int newSum = state.first + numbers[state.second];
            int newState = state.second + 1;
            q.push(make_pair(newSum, newState));

            // Subtraction case
            newSum = state.first - numbers[state.second];
            q.push(make_pair(newSum, newState));
        }
    }
    return answer;
}
