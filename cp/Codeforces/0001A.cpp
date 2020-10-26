#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ll n, m, a;
    ll hor, vert;

    cin >> n >> m >> a;

    if (n % a == 0) {
        hor = n / a;
    } else {
        hor = n / a + 1;
    }

    if (m % a == 0) {
        vert = m / a;
    } else {
        vert = m / a + 1;
    }

    cout << (hor * vert);
}
