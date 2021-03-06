#ifndef SELECTIONSORT_CPP
#define SELECTIONSORT_CPP

#include <algorithm>

/* @brief Selection Sort algorithm */
void selectionSort(int arr[], long len) {
    for (long i = len - 1; i >= 0; --i) {
        long maxInd = 0;
        for (long j = 1; j <= i; j++) {
            if (arr[maxInd] < arr[j]) {
                maxInd = j;
            }
        }

        // swap maximum into its place
        std::swap(arr[i], arr[maxInd]);
    }
}

#endif // SELECTIONSORT_CPP
