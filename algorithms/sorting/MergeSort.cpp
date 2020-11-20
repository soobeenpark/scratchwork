#ifndef MERGESORT_CPP
#define MERGESORT_CPP

#include "helpers.cpp"

/* @brief: Merges two sorted subarrays (left and right) into one full sorted
 * array.
 *
 * Args:
 *  arr: The array containing left and right halves that we want to merge.
 *  len: The length of the array.
 *  boundary: The index of the array that separates left and right halves.
 */
void merge(int arr[], long len, int boundary) {
    int tmp[len];

    int iter = 0;
    int left1 = 0;
    int left2 = boundary;

    while (iter < len) {
        if (left1 < boundary && (left2 == len || arr[left1] < arr[left2])) {
            tmp[iter++] = arr[left1++];
        } else {
            tmp[iter++] = arr[left2++];
        }
    }
    copyArray(arr, tmp, len);
}

/* @brief Merge Sort algorithm #1
 *
 * Uses a recursive top-down approach
 */
void mergeSortTopDown(int arr[], long len) {
    // Recursive base case
    if (len == 0 || len == 1) {
        // Nothing to do -- arr with one or no elements is already sorted!
        return;
    }

    long mid = len / 2;        // integer division
    long rightLen = len - mid; // integer division

    // First sort left and right halves
    mergeSortTopDown(arr, mid);
    mergeSortTopDown(arr + mid, rightLen);

    // Next, merge the sorted left and right halves
    merge(arr, len, mid);
}

/* @brief Merge Sort algorithm #2
 *
 * Uses an iterative bottom-up approach
 */
void mergeSortBottomUp(int arr[], long len) {
    // Subarrays (bins) of size 1 -> 2 -> 4 -> 8 -> ...
    for (long binSize = 1; binSize < len; binSize *= 2) {

        // Iterate through all bins, in pairs of 2
        // (adjacent neighbors are merged together).
        for (long whichBin = 0; whichBin < len - binSize;
             whichBin += binSize * 2) {

            long binsLength = std::min(binSize * 2, len - whichBin);
            merge(arr + whichBin, binsLength, binSize);
        }
    }
}

#endif // MERGESORT_CPP
