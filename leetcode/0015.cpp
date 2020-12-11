#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        // Initialize answer vector
        vector<vector<int>> ans;

        // Sort the array
        sort(nums.begin(), nums.end());

        // Iterate through the array, fixing the first element
        for (int i = 0; i < (int)nums.size() - 2; i++) {
            // Two sum on subarray
            int target = -nums[i];
            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right) {
                int numLeft = nums[left];
                int numRight = nums[right];

                if (numLeft + numRight == target) {
                    ans.push_back({nums[i], nums[left], nums[right]});

                    // Roll left forward to avoid duplicates
                    while (left < right && numLeft == nums[left]) {
                        left++;
                    }

                    // Roll right backwards to avoid duplicates
                    while (left < right && numRight == nums[right]) {
                        right--;
                    }
                } else if (numLeft + numRight < target) {
                    left++;
                } else {
                    right--;
                }
            }

            // Roll i forward to avoid duplicates
            while (i < (int)nums.size() - 2 && nums[i + 1] == nums[i]) {
                i++;
            }
        }
        return ans;
    }
};
