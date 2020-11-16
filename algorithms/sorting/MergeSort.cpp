#ifndef MERGESORT_CPP
#define MERGESORT_CPP

#include "helpers.cpp"

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

    long len1 = len / 2;    // integer division
    long len2 = len - len1; // integer division

    // First sort left and right halves
    mergeSortTopDown(arr, len1);
    mergeSortTopDown(arr + len1, len2);

    // Next, merge the sorted left and right halves
    long i1 = 0, i2 = len1;
    long tmpIndex = 0;

    // Initialize new tmp array
    int *tmp = new int[len];

    // Put elements from left and right halves in order into new tmp array
    while (tmpIndex < len) {
        // If i1 is within range, and either i2 is out of range or
        // arr[i1] < arr[i2], then we process the left half.
        // Otherwise, we process the right half.
        if (i1 < len1 && (i2 >= len || arr[i1] < arr[i2])) {
            tmp[tmpIndex++] = arr[i1++];
        } else {
            tmp[tmpIndex++] = arr[i2++];
        }
    }

    // Deep copy tmp elements back into original array
    copyArray(arr, tmp, len);

    // Before exiting, clean up allocated tmp array
    delete[] tmp;
}

/* @brief Merge Sort algorithm #2
 *
 * Uses a bottom-up approach
 */
void mergeSortBottomUp(int arr[], long len) {
    // Subarrays (bins) of size 1 -> 2 -> 4 -> 8 -> ...
    for (long binSize = 1; binSize < len; binSize *= 2) {

        // Iterate through all bins, in pairs of 2
        // (adjacent neighbors are merged together).
        for (long whichBin = 0; whichBin < len - binSize;
             whichBin += binSize * 2) {

            // Set temp working array
            int *tmp = new int[len];

            // Initialize indices
            long i1 = whichBin;
            long i2 = i1 + binSize;
            long tempIndex = whichBin;

            // Establish index access bounds for left and right subarrays
            long leftBinBound = whichBin + binSize;
            long rightBinBound = std::min(whichBin + binSize * 2, len);

            // Merge adjacent bins together
            while (tempIndex < rightBinBound) {

                // If i1 is within range, and either i2 is out of range or
                // arr[i1] < arr[i2], then we process the left half.
                // Otherwise, we process the right half.
                if (i1 < leftBinBound &&
                    (i2 >= rightBinBound || arr[i1] < arr[i2])) {
                    tmp[tempIndex++] = arr[i1++];
                } else {
                    tmp[tempIndex++] = arr[i2++];
                }
            }

            // Copy back temp elements into original array
            copyArray(arr + whichBin, tmp + whichBin, rightBinBound - whichBin);

            // Make sure to clean up allocated tmp array
            delete[] tmp;
        }
    }
}

#endif // MERGESORT_CPP
