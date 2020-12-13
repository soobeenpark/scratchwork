#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t, k, d;
    cin >> n >> t >> k >> d;

    bool cakesRemainAfterBuild = n > (d/t + 1)*k;
    string output = cakesRemainAfterBuild ? "YES" : "NO";
    cout << output << endl;
}
