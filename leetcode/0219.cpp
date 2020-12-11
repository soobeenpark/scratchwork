#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_set<int> seen;
        int i = 0;
        // Process first k elements in nums
        while (i < nums.size() && i <= k) {
            if (seen.find(nums[i]) != seen.end()) {
                return true;
            }
            seen.insert(nums[i]);
            i++;
        }

        // Process rest (k+1 to nums.size())
        while (i < nums.size()) {
            // Remove i-(k+1)th element from seen set
            seen.erase(nums[i - k - 1]);
            if (seen.find(nums[i]) != seen.end()) {
                return true;
            }
            seen.insert(nums[i]);
            i++;
        }
        return false;
    }
};

class SolutionBetter {
  public:
    // Same algorithm as above, but a lot cleaner
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_set<int> seen;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) {
                seen.erase(nums[i - k - 1]);
            }
            if (seen.find(nums[i]) != seen.end()) {
                return true;
            }
            seen.insert(nums[i]);
        }
        return false;
    }
};

class SolutionAlt {
  public:
    // Solution using map instead of set - more space, less time (no erase)
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int> seen; // <value, index>
        for (int i = 0; i < nums.size(); i++) {
            if (seen.count(nums[i]) && i - seen[nums[i]] <= k) {
                return true;
            }
            seen[nums[i]] = i;
        }
        return false;
    }
}
