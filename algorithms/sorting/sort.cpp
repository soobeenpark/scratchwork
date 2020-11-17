// sort.cpp
// Test out various sorting algorithms!

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "InsertionSort.cpp"
#include "MergeSort.cpp"
#include "SelectionSort.cpp"
#include "QuickSort.cpp"
#include "helpers.cpp"

/* Global constants */
const int NUM_ALGORITHMS = 5;

// Test different sorting algorithms
int main(int argc, char *argv[]) {
    // Checking argument was passed in properly
    if (argc != 2) {
        std::cout << "Please enter the size of the array as first arg\n";
        exit(1);
    }

    // Convert argument value from cstring to long
    char *endptr = nullptr;
    long len = strtol(argv[1], &endptr, 10);

    // Error checking for args passed in
    if (len < 1 || (strcmp(argv[1], "\0") == 0) || *endptr != '\0') {
        std::cout << "Please enter a valid integer of at least 1" << std::endl;
        exit(1);
    }

    // Create a random array (used as an original for multiple copies to be made
    // of)
    int *arr = new int[len];
    createArray(arr, len);

    // Copies of unsorted arr will be held so that each algorithm can operate
    // on its own copy of the unsorted array.
    int *unsortedArraysList[NUM_ALGORITHMS];

    // Create new unsorted copies of lists
    for (int i = 0; i < NUM_ALGORITHMS; ++i) {
        unsortedArraysList[i] = new int[len];
        copyArray(unsortedArraysList[i], arr, len);
    }

    // Print out array before sorting
    printArray(arr, len);
    std::cout << "Before Sorting" << std::endl;

    // Do the sorts and print out before / after results
    for (int i = 0; i < NUM_ALGORITHMS; ++i) {
        // Do the sort
        if (i == 0) {
            selectionSort(unsortedArraysList[i], len);
        } else if (i == 1) {
            mergeSortTopDown(unsortedArraysList[i], len);
        } else if (i == 2) {
            mergeSortBottomUp(unsortedArraysList[i], len);
        } else if (i == 3) {
            quickSort(unsortedArraysList[i], len);
        } else if (i == 4) {
            insertionSort(unsortedArraysList[i], len);
        }

        // Print out array after sorting
        printArray(unsortedArraysList[i], len);

        // Print out name of the sort
        std::string sortName;
        if (i == 0) {
            sortName = "Selection Sort";
        } else if (i == 1) {
            sortName = "Merge Sort Top Down";
        } else if (i == 2) {
            sortName = "Merge Sort Bottom Up";
        } else if (i == 3) {
            sortName = "Quick Sort";
        } else if (i == 4) {
            sortName = "Insertion Sort";
        }
        std::cout << sortName;

        // Check that the sort worked properly
        sortChecker(unsortedArraysList[i], len);
        std::cout << std::endl;
    }

    // Delete the dynamically allocated original array
    delete[] arr;

    // Delete copies of the unsorted lists
    for (int i = 0; i < NUM_ALGORITHMS; ++i) {
        delete[] unsortedArraysList[i];
    }

    // Normal exit
    return 0;
}
