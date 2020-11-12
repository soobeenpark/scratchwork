// Minimum Cost For Tickets

#include <bits/stdc++.h>

using namespace std;

const int NUM_DAYS = 365;

class Solution {
    // Uses recursive dynamic programming
  public:
    unordered_set<int> set;
    vector<int> dp;
    vector<bool> visited;
    vector<int> cst;

    int solve(int day) {
        if (day <= 0) {
            return 0;
        }
        if (visited[day]) {
            return dp[day];
        }
        if (find(set.begin(), set.end(), day) == set.end()) {
            dp[day] = solve(day - 1);
        } else {
            dp[day] = min({solve(day - 1) + cst[0], solve(day - 7) + cst[1],
                           solve(day - 30) + cst[2]});
        }
        visited[day] = true;
        return dp[day];
    }

    int mincostTickets(vector<int> &days, vector<int> &costs) {
        cst = costs;
        int lastDay = days[days.size() - 1];
        dp = vector<int>(lastDay + 1, 0);
        visited = vector<bool>(lastDay + 1, false);
        set = unordered_set<int>(days.begin(), days.end());

        return solve(lastDay);
    }
};

class SolutionAlternate {
    // Uses iterative dynamic programming
  public:
    int mincostTickets(vector<int> &days, vector<int> &costs) {
        int lastDay = days[days.size() - 1];
        vector<int> dp(lastDay + 1, 0);
        unordered_set<int> set(days.begin(), days.end());

        for (int i = 1; i <= lastDay; i++) {
            if (find(set.begin(), set.end(), i) == set.end()) {
                dp[i] = dp[i - 1];
            } else {
                dp[i] = min({dp[i - 1] + costs[0], dp[max(0, i - 7)] + costs[1],
                             dp[max(0, i - 30)] + costs[2]});
            }
        }
        return dp[lastDay];
    }
};
