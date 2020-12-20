#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> mapp;
    string row;

    while (cin >> row) {
        mapp.push_back(row);
    }

    long long slope1 = 0;
    for (size_t i = 0; i < mapp.size(); i++) {
        row = mapp[i];
        slope1 += row[i*3 % row.size()] == '#';
    }
    cout << slope1 << endl;
}
