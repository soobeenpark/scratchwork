#ifndef INSERTIONSORT_CPP
#define INSERTIONSORT_CPP

#include <algorithm>

/* @brief Insertion Sort algorithm */
void insertionSort(int arr[], long len) {
    for (int i = 1; i < len; i++) { // Loop invariant: arr[0, i) is sorted
        for (int j = 0; j < i; j++) {
            if (arr[j] >= arr[i])
                std::swap(arr[i], arr[j]);
        }
    }
}

void insertionSortAlternate(int arr[], long len) {
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

#endif // INSERTIONSORT_CPP
