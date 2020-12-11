#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
  public:
    // Total O(n logk) algorithm
    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
        set<ll> seen;
        // Iterate O(n) times
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) {
                seen.erase(nums[i - k - 1]);
            }
            // O(log k) operation
            auto lb = seen.lower_bound((ll)nums[i] - t);
            if (lb != seen.end() && *lb <= (ll)nums[i] + t) {
                return true;
            }
            seen.insert(nums[i]);
        }
        return false;
    }
};

// Better way in O(n) using bucket sort possible??
