#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int minprice = INT_MAX;
        int maxprofit = 0;
        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < minprice) {
                minprice = prices[i];
            }
            if (maxprofit < prices[i] - minprice) {
                maxprofit = prices[i] - minprice;
            }
        }
        return maxprofit;
    }
}
