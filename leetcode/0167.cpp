#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        // Two pointer method
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int l = nums[left];
            int r = nums[right];
            if (l + r == target) {
                return {left + 1, right + 1};
            } else if (l + r < target) {
                left++;
            } else {
                right--;
            }
        }
        return {-1, -1};
    }
};
