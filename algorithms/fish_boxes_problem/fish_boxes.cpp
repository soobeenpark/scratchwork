#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000;
double dp[MAX][MAX];
int totalDays;

double search(vector<int> stack1, vector<int> stack2, int top1, int top2) {
    if (top1 + top2 == totalDays) {
        return 0;
    }

    if (dp[top1][top2] != -1) {
        return dp[top1][top2];
    }

    double ans = INT_MIN;
    if (top1 != (int)stack1.size()) {
        ans = max(ans, 0.9 * search(stack1, stack2, top1 + 1, top2) + stack1[top1]);
    }
    if (top2 != (int)stack2.size()) {
        ans = max(ans, 0.9 * search(stack1, stack2, top1, top2 + 1) + stack2[top2]);
    }

    dp[top1][top2] = ans;
    return ans;
}

double solution(vector<int> stack1, vector<int> stack2) {
    // dp contains the best profit made with each of top1 and top2 amt sold
    for (int i1 = 0; i1 <= (int)stack1.size(); i1++) {
        for (int i2 = 0; i2 <= (int)stack2.size(); i2++) {
            dp[i1][i2] = -1;
        }
    }

    // Do a dfs with dp
    // times 10 to reflect $10 per kg
    return 10 * search(stack1, stack2, 0, 0);
}

int main() {
    vector<int> stack1 = {40, 10, 50};
    vector<int> stack2 = {20, 20, 60};
    totalDays = stack1.size() + stack2.size();

    double profit = solution(stack1, stack2);
    cout << profit << endl;
}
