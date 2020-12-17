#include <iostream>
#include <vector>
#include <string>

using namespace std;

void test_case(vector<int> tn) {
    int target;
    cin >> target;

    int sz = tn.size();
    for (int i = 0; i < sz; i++) {
        for (int j = i; j < sz; j++) {
            for (int k = j; k < sz; k++) {
                if (tn[i] + tn[j] + tn[k] == target) {
                    cout << true << endl;
                    return;
                }
            }
        }
    }
    cout <<  false << endl;
}

int main() {
    int T;
    cin >> T;

    vector<int> triangular_nums(1000, 0);
    int tn = 1;
    int i = 0;
    while (tn <= 1000) {
        triangular_nums[i++] = tn;
        tn += (i + 1);
    }
    triangular_nums.resize(i-1);

    while (T--) {
        test_case(triangular_nums);
    }
}
