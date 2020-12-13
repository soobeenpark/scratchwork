#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int aStamina, bStamina;
        cin >> aStamina >> bStamina;

        aStamina--;  // Alice serves first

        cout << aStamina << " " << bStamina << endl;
    }
}
