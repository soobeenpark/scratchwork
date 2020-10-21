#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

/* Hash Table implementation
 *
 * Time: O(n), where n is length of either aStr and/or bStr.
 * Space: O(n)
 */
bool isPermutation_v1(std::string aStr, std::string bStr) {
    if (aStr.length() != bStr.length()) {
        return false;
    }

    std::unordered_map<char, int> charMap;
    
    // O(n) since n amounts of O(1) (amortized) insertions into hash table.
    for (size_t i = 0; i < aStr.length(); i++) {
        ++charMap[aStr[i]];
    }

    // Also O(n)
    for (size_t i = 0; i < bStr.length(); i++) {
        char c = bStr[i];
        if (charMap.find(c) == charMap.end()) {
            // bStr has character that aStr doesn't.
            return false;
        } else {
            assert(charMap[c] > 0);
            --charMap[c];
            if (charMap[c] == 0) {
                charMap.erase(c);
            }
        }
    }

    // If charMap is empty, then we know bStr chars all match aStr chars.
    return charMap.empty();
}

/* Sorting implementation
 *
 * Time: O(nlogn), where n is the length of either aStr and/or bStr.
 * Space: O(1)
 *
 * NOTE: Although the asymptotic complexity is O(nlogn) and thus worse than
 *      version 1, it can be argued that the sorting is only done once at the
 *      beginning and the rest of the algorithm is O(n), and so it runs
 *      comparably to version 1. This version doesn't have to compute an
 *      expensive hash for each character in the strings.
 *      See the competitive programmer's handbook Ch4 for a fuller discussion.
 */
bool isPermutation_v2(std::string aStr, std::string bStr) {
    if (aStr.length() != bStr.length()) {
        return false;
    }

    std::sort(aStr.begin(), aStr.end());
    std::sort(bStr.begin(), bStr.end());

    for (size_t i = 0; i < aStr.length(); ++i) {
        if (aStr[i] != bStr[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    std::string s1 = "abde";
    std::string s2 = "abde";
    std::string s3 = "aebd";
    std::string s4 = "abe";
    std::string s5 = "axeb";
    std::string s6 = "abbb";
    std::string empty = "";

    // Test version 1
    if (!isPermutation_v1(s1, s2)) {
        std::cout << "Test 1 FAIL" << std::endl;
    }

    if (!isPermutation_v1(s1, s3)) {
        std::cout << "Test 2 FAIL" << std::endl;
    }

    if (isPermutation_v1(s1, s4)) {
        std::cout << "Test 3 FAIL" << std::endl;
    }

    if (isPermutation_v1(s1, s5)) {
        std::cout << "Test 4 FAIL" << std::endl;
    }

    if (isPermutation_v1(s1, s6)) {
        std::cout << "Test 5 FAIL" << std::endl;
    }

    if (isPermutation_v1(s1, empty)) {
        std::cout << "Test 6 FAIL" << std::endl;
    }

    // Test version 2
    if (!isPermutation_v2(s1, s2)) {
        std::cout << "Test 1 FAIL" << std::endl;
    }

    if (!isPermutation_v2(s1, s3)) {
        std::cout << "Test 2 FAIL" << std::endl;
    }

    if (isPermutation_v2(s1, s4)) {
        std::cout << "Test 3 FAIL" << std::endl;
    }

    if (isPermutation_v2(s1, s5)) {
        std::cout << "Test 4 FAIL" << std::endl;
    }

    if (isPermutation_v2(s1, s6)) {
        std::cout << "Test 5 FAIL" << std::endl;
    }

    if (isPermutation_v2(s1, empty)) {
        std::cout << "Test 6 FAIL" << std::endl;
    }
    

    std::cout << "Tests finished" << std::endl;
}
