#include <iostream>
#include <vector>
#include <string>

using namespace std;

void test_case(vector<int> tn) {
    int target;
    cin >> target;

    int sz = tn.size();
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < sz; k++) {
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
    triangular_nums.resize(i);

    while (T--) {
        test_case(triangular_nums);
    }
}
