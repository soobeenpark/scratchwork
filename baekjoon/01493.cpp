#include <iostream>
#include <vector>

const int MAX_CUBE_TYPE = 20;
int availableBoxes[MAX_CUBE_TYPE];

// Returns the floor(log2()) of side of the largest available box with side <= shortestSide
// If no box that fits is available, returns -1
int getBiggestBoxSideIdx(int shortestSide) {
    if (shortestSide == 0) {
        return -1;
    }

    // Get floor(log_2(shortestSide))
    int floorLog2 = -1;
    while (shortestSide) {
        floorLog2++;
        shortestSide = shortestSide >> 1;
    }

    while (floorLog2 >= 0) {
        if (availableBoxes[floorLog2] > 0) {
            return floorLog2;
        }
        floorLog2--;
    }

    // No suitable box found
    return -1;
}

// Returns the minimum amount of boxes needed to fill up given space of
// length, width, and height.
// If the space can't be filled with available boxes, -1 is returned.
int numBoxes(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return 0;
    }

    int shortestSide = std::min(length, std::min(width, height));
    int boxIdx = getBiggestBoxSideIdx(shortestSide);

    if (boxIdx == -1) {
        return -1;
    }
    availableBoxes[boxIdx]--; // mark box as used

    int boxSide = 1 << boxIdx;
    int subNumBoxes1 = numBoxes(boxSide, width-boxSide, height);
    if (subNumBoxes1 == -1) {
        availableBoxes[boxIdx]++;
        return -1;
    }
    int subNumBoxes2 = numBoxes(boxSide, boxSide, height-boxSide);
    if (subNumBoxes2 == -1) {
        availableBoxes[boxIdx]++;
        return -1;
    }
    int subNumBoxes3 = numBoxes(length-boxSide, width, height);
    if (subNumBoxes3 == -1) {
        availableBoxes[boxIdx]++;
        return -1;
    }
    
    return 1 + subNumBoxes1 + subNumBoxes2 + subNumBoxes3;
}

int main() {
    // Initialize l, w, h of box
    int l, w, h;
    std::cin >> l >> w >> h;

    // Initialize availableBoxes array
    std::fill(availableBoxes, availableBoxes+MAX_CUBE_TYPE, 0);
    int n;
    std::cin >> n;
    while (n--) {
        int cubeType;
        std::cin >> cubeType;
        std::cin >> availableBoxes[cubeType];
    }

    std::cout << numBoxes(l, w, h) << std::endl;
}

