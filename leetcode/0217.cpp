#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool containsDuplicate(vector<int> &nums) {
        unordered_set<int> htable(nums.begin(), nums.end());
        return htable.size() != nums.size();
    }
};
