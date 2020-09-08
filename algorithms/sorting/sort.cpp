// sort.cpp
// Test out various sorting algorithms!

#include <iostream>
#include <cassert>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <random>

/* Global constants */
const int NUM_ALGORITHMS = 3;

/************************************************************
 * Helper Functions
 ************************************************************/
/* @brief Creates an array and returns it
*/
void createArray(int *arr, long len) {
    // random number generation
    std::random_device rd; // used to obtain seed for rand number engine
    std::mt19937 gen(rd()); // mersenne_twister engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 99);
    for (long i=0; i<len; ++i) {
        arr[i] = (int)distrib(gen);
    }
}

/* @brief Prints array elements one by one on same line
*/
void printArray(int arr[], long len) {
    std::cout << "[ ";
    for (long i=0; i<len; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\t";
}

/* @brief Checks if array is sorted properly
 * 
 * Exits program if not sorted properly
 */
void sortChecker(int arr[], long len) {
    bool sorted;
    int prev = arr[0];
    int curr;
    for (long i=1; i<len; ++i) {
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
    for (long i=0; i<len; ++i) {
        dest[i] = source[i];
    }
}


/************************************************************
 * Sorting Algorithms
 ************************************************************/
/* @brief Selection Sort algorithm
*/
void selectionSort(int arr[], long len) {
    for (long i=len-1; i>=0; --i) {
        long maxInd = 0;
        for (long j=1; j<=i; j++) {
            if (arr[maxInd] < arr[j]) {
                maxInd = j;
            }
        }

        // swap maximum into its place
        int tmp = arr[i];
        arr[i] = arr[maxInd];
        arr[maxInd] = tmp;
    }
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

    long len1 = len / 2; // integer division
    long len2 = len - len1; // integer division
    
    // First sort left and right halves
    mergeSortTopDown(arr, len1);
    mergeSortTopDown(arr+len1, len2);

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

    /*
    // Exercise: Why does this (instead of copyArray() above) not work?
    arr = tmp;
    */

    // Before exiting, clean up allocated tmp array
    delete [] tmp;
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
        for (long whichBin = 0; whichBin < len - binSize; whichBin += binSize * 2) {

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
                if (i1 < leftBinBound && (i2 >= rightBinBound || arr[i1] < arr[i2])) {
                    tmp[tempIndex++] = arr[i1++];
                } else {
                    tmp[tempIndex++] = arr[i2++];
                }
            }

            // Copy back temp elements into original array
            copyArray(arr + whichBin, tmp + whichBin, rightBinBound - whichBin);

            // Make sure to clean up allocated tmp array
            delete [] tmp;
        }

    }

}

/************************************************************
 ************************************************************/
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
        std::cout << "Please enter a valid integer greater than 1" << std::endl;
        exit(1);
    }

    // Create a random array (used as an original for multiple copies to be made of)
    int *arr= new int[len];
    createArray(arr, len);

    // Copies of unsorted arr will be held so that each algorithm can operate
    // on its own copy of the unsorted array.
    int *unsortedArraysList[NUM_ALGORITHMS];

    // Create new unsorted copies of lists
    for (int i=0; i<NUM_ALGORITHMS; ++i) {
        unsortedArraysList[i] = new int[len];
        copyArray(unsortedArraysList[i], arr, len);
    }

    // Print out array before sorting 
    printArray(arr, len);
    std::cout << "Before Sorting" << std::endl;
    
    // Do the sorts and print out before / after results 
    for (int i=0; i<NUM_ALGORITHMS; ++i) {
        // Do the sort
        if (i == 0) {
            selectionSort(unsortedArraysList[i], len);
        } else if (i == 1) {
            mergeSortTopDown(unsortedArraysList[i], len);
        } else if (i == 2) {
            mergeSortBottomUp(unsortedArraysList[i], len);
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
        }
        std::cout << sortName;

        // Check that the sort worked properly
        sortChecker(unsortedArraysList[i], len);
        std::cout << std::endl;
    }

    // Delete the dynamically allocated original array
    delete [] arr;

    // Delete copies of the unsorted lists
    for (int i=0; i<NUM_ALGORITHMS; ++i) {
        delete [] unsortedArraysList[i]; 
    }

    // Normal exit
    return 0;
}
