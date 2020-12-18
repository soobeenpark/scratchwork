#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    vector<int> nums;
    int x;
    while (cin >> x) {
        nums.push_back(x);
    }

    for (int i = 0; i < (int)nums.size()-2; i++) {
        int target = 2020 - nums[i];

        // two sum
        unordered_set<int> htable;
        for (int j = 0; j < (int)nums.size(); j++) {
            int subtarget = target - nums[j];
            if (htable.count(subtarget)) {
                cout << nums[i] * nums[j] * subtarget << endl;
                return 0;
            }
            htable.insert(nums[j]);
        }
    }
}
