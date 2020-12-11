#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int ans = 0;
        bool haveStock = false;
        int boughtPrice = 0;
        for (int day = 0; day < prices.size() - 1; day++) {
            if (prices[day] > prices[day + 1]) {
                if (haveStock) {
                    // sell today
                    ans += (prices[day] - boughtPrice);
                    haveStock = false;
                }
            } else {
                if (!haveStock) {
                    // buy today
                    boughtPrice = prices[day];
                    haveStock = true;
                }
            }
        }

        if (haveStock) {
            ans += prices[prices.size() - 1] - boughtPrice;
        }
        return ans;
    }
};

class SolutionAlt1 {
  public:
    // Using peak and valley approach
    int maxProfit(vector<int> &prices) {
        int i = 1;
        int ans = 0;
        int valley = prices[0];
        int peak = prices[0];
        while (i < prices.size()) {
            while (i < prices.size() && prices[i] < prices[i - 1]) {
                i++;
            }
            valley = prices[i - 1];
            while (i < prices.size() && prices[i] >= prices[i - 1]) {
                i++;
            }
            peak = prices[i - 1];
            ans += (peak - valley);
        }
        return ans;
    }
};

class SolutionAlt2 {
  public:
    // Using consecutive slope adding approach
    int maxProfit(vector<int> &prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i - 1] < prices[i]) {
                ans += prices[i] - prices[i - 1];
            }
        }
        return ans;
    }
};

class SolutionBruteForce {
  public:
    int maxProfit(vector<int> &prices) {
        return calculate(prices, 0);
    }

    int calculate(vector<int> &prices, int day) {
        if (day >= prices.size()) {
            return 0;
        }

        int maximum = 0;
        for (int start = day; start < prices.size(); start++) {
            int maxprofit = 0;
            for (int end = start + 1; end < prices.size(); end++) {
                int profit = 0;
                if (prices[start] < prices[end]) {
                    profit = calculate(prices, end + 1) + prices[end] -
                             prices[start];
                }

                maxprofit = max(maxprofit, profit);
            }
            maximum = max(maximum, maxprofit);
        }
        return maximum;
    }
};
