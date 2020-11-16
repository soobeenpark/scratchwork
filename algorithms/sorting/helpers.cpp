#ifndef HELPERS_CPP
#define HELPERS_CPP

#include <algorithm>
#include <iostream>
#include <random>

/* @brief Creates an array and returns it
 */
void createArray(int *arr, long len) {
    // random number generation
    std::random_device rd;  // used to obtain seed for rand number engine
    std::mt19937 gen(rd()); // mersenne_twister engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 99);
    for (long i = 0; i < len; ++i) {
        arr[i] = (int)distrib(gen);
    }
}

/* @brief Prints array elements one by one on same line
 */
void printArray(int arr[], long len) {
    std::cout << "[ ";
    for (long i = 0; i < len; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\t";
}

/* @brief Checks if array is sorted properly
 *
 * Exits program if not sorted properly
 */
void sortChecker(int arr[], long len) {
    int prev = arr[0];
    int curr;
    for (long i = 1; i < len; ++i) {
        curr = arr[i];
        if (prev > curr) {
            std::cout << "\t<===== Sorting Failed" << std::endl;
            exit(1);
        }

        prev = curr;
    }
}

/* @brief Copies elements of one array into another array
 */
void copyArray(int dest[], int source[], long len) {
    for (long i = 0; i < len; ++i) {
        dest[i] = source[i];
    }
}

#endif // HELPERS_CPP
