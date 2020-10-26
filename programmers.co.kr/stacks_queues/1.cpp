// https://programmers.co.kr/learn/courses/30/lessons/42584
// Stock Prices

#include <stack>
#include <string>
#include <vector>

using namespace std;

void processPop(vector<int> &answer, stack<int> &st, int currentInd) {
    answer[st.top()] = currentInd - st.top();
    st.pop();
}

vector<int> solution(vector<int> prices) {
    int len = prices.size();
    vector<int> answer(len, 0);
    stack<int> st;

    for (int i = 0; i < len; i++) {
        while (!st.empty() && prices[st.top()] > prices[i]) {
            processPop(answer, st, i);
        }
        st.push(i);
    }

    while (!st.empty()) {
        processPop(answer, st, len - 1);
    }
    return answer;
}
