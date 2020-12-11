#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> htable;
        for (int i = 0; i < nums.size(); i++) {
            int curr = nums[i];
            int matching = target - curr;
            if (htable.find(matching) != htable.end()) {
                return {htable.find(matching)->second, i};
            }
            htable.insert({curr, i});
        }
        return {-1, -1};
    }
};
