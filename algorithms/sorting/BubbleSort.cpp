#ifndef BUBBLESORT_CPP
#define BUBBLESORT_CPP

#include <algorithm>

/* @brief Bubble Sort algorithm */
void bubbleSort(int arr[], long len) {
    for (long i = 0; i < len; i++) {
        // Loop Invariant: A[len-i, len) >= A[0, len-i)
        for (long j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

#endif // BUBBLESORT_CPP
