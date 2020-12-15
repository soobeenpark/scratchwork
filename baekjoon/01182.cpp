#include <bits/stdc++.h>
using namespace std;

int N, S;

int search(int *arr, int depth, int sum) {
    if (depth == N) {
        return sum == S;
    }
    int ans = 0;

    ans += search(arr, depth + 1, sum);
    ans += search(arr, depth + 1, sum + arr[depth]);
    return ans;
}

int main() {
    cin >> N >> S;
    int arr[N];

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int count = search(arr, 0, 0);

    if (S == 0) {
        count--;
    }
    cout << count << endl;
}
