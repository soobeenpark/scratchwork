#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> htable;
    int x;
    while (cin >> x) {
        int y = 2020 - x;
        if (htable.find(y) != htable.end()) {
            cout << x * y << endl;
            return 0;
        }
        htable.insert(x);
    }
}
