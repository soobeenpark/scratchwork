/* @file: max-subarray-sum.cpp
 * @author: Soobeen Park
 *
 * Testing algorithms from Competitive Programmer's Handbook
 * for the Maximum Subarray Sum problem
 * (cses.fi/book/book.pdf - Chapter 2)
 *
 */

#include <bits/stdc++.h>

using namespace std;

/* @brief Implements max subarray sum using O(n^3) algorithm */
void maxSubarraySum1(int n, int arr[]) {
    int best = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int sum = 0;
            for (int k = i; k <= j; ++k) {
                sum += arr[k];
            }
            best = max(sum, best);
        }
    }
    cout << "v1: " << best << endl;
}

/* @brief Implements max subarray sum using O(n^2) algorithm */
void maxSubarraySum2(int n, int arr[]) {
    int best = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j < n; ++j) {
            sum += arr[j];
            best = max(best, sum);
        }
    }
    cout << "v2: " << best << endl;
}

int main() {
    int n = 7;
    int arr[] = {-1, 2, 4, -3, 5, -5, 2};

    maxSubarraySum1(n, arr);
    maxSubarraySum2(n, arr);
}

