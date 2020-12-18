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
    long long slope2 = 0;
    long long slope3 = 0;
    long long slope4 = 0;
    long long slope5 = 0;
    for (size_t i = 0; i < mapp.size(); i++) {
        row = mapp[i];
        slope1 += row[i % row.size()] == '#';
        slope2 += row[i*3 % row.size()] == '#';
        slope3 += row[i*5 % row.size()] == '#';
        slope4 += row[i*7 % row.size()] == '#';
        slope5 += (i % 2 == 0) && (row[i/2 % row.size()] == '#');
    }
    cout << slope1 * slope2 * slope3 * slope4 * slope5 << endl;
}
