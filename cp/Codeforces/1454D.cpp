#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> factors;

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll n;
        cin >> n;

        // Set factors
        factors = vector<ll>(100001, 0);

        // Decompose n into its factors (prime factorization of n)
        ll nCopy = n;
        for (ll i = 2; i <= sqrt(n); i++) {
            while (n % i == 0) {
                factors[i]++;
                n /= i;
            }
        }

        // Find most frequently occurring factor, and use that in answer
        int mostCommonFactor = distance(
            factors.begin(), max_element(factors.begin(), factors.end()));
        if (factors[mostCommonFactor] == 0) {
            // If all factors in array 0, n is prime number
            cout << 1 << endl;
            cout << nCopy << endl;
        } else {
            int count = factors[mostCommonFactor];
            cout << count << endl;
            for (int i = 0; i < count - 1; i++) {
                cout << mostCommonFactor << " ";
                nCopy /= mostCommonFactor;
            }
            cout << nCopy << endl;
        }
    }
}
