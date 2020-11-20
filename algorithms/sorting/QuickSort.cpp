#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#include <algorithm>
#include <cassert>

/* @brief Returns the pivot index after performing partition on array
 */
int partition(int arr[], int len) {
    /* Note on choosing initial pivot index:
     * Quick Sort's run time complexity depends on choosing a "good" pivot
     * index. Here, we simply just choose the first index as the pivot element.
     * This is not usually the best approach, as this often fails to be
     * efficient on arrays that are almost sorted.
     * However, since our tests are run on randomized array elements, we make
     * this simplification for now. */
    int pivotIndex = 0;
    int left = 1;
    int right = len;

    while (left < right) {
        if (arr[pivotIndex] > arr[left]) {
            left++;
        } else {
            right--;
            std::swap(arr[left], arr[right]);
        }
    }
    assert(left == right);
    std::swap(arr[pivotIndex], arr[left - 1]); // put pivot in place
    return left - 1;
}

/* @brief Quick Sort algorithm */
void quickSort(int arr[], long len) {
    if (len == 0 || len == 1) {
        return;
    }

    int p = partition(arr, len);
    quickSort(arr, p);
    quickSort(arr + p + 1, len - (p + 1));
}

#endif // QUICKSORT_CPP
