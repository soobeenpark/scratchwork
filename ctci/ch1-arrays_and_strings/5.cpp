#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

/* Helper method
 * Precondition: aStr and bStr have the same lengths.
 *
 * Let n be the length of the string.
 * Time: O(n)
 * Space: O(1)
 */
bool oneAwayReplace(std::string aStr, std::string bStr) {
    assert(aStr.length() == bStr.length());
    bool foundMismatch = false;
    for (size_t i = 0; i < aStr.length(); i++) {
        if (aStr[i] != bStr[i]) {
            if (foundMismatch) {
                return false;
            }
            foundMismatch = true;
        }
    }
    return true;
}

/* Helper method
 * Precondition: aStr is 1 shorter than bStr in length.
 *
 * Time: O(n)
 * Space: O(1)
 */
bool oneAwayInsert(std::string aStr, std::string bStr) {
    assert(aStr.length() + 1 == bStr.length());
    bool foundMismatch = false;
    for (size_t ai = 0, bi = 0; ai < aStr.length(); ai++, bi++) {
        if (aStr[ai] != bStr[bi]) {
            if (foundMismatch) {
                return false;
            }
            foundMismatch = true;
            // Keep bi at same position while ai moves ahead
            ai--;
        }
    }
    return true;
}


/* Time: O(n)
 * Space: O(1)
 */
bool oneAway(std::string aStr, std::string bStr) {
    if (aStr.length() == bStr.length()) {
        return oneAwayReplace(aStr, bStr);
    } else if (aStr.length() + 1 == bStr.length()) {
        return oneAwayInsert(aStr, bStr);
    } else if (bStr.length() + 1 == aStr.length()) {
        return oneAwayInsert(bStr, aStr);
    } else {
        return false;
    }
}


/* Combined version of Replace and Insert
 * Removes code duplication, but may sacrifice some readability.
 *
 * Time: O(n)
 * Space: O(1)
 */
bool oneAwayCombined(std::string aStr, std::string bStr) {
    std::string longer = aStr.length() < bStr.length() ? bStr : aStr;
    std::string shorter = aStr.length() < bStr.length() ? aStr : bStr;

    // Length check
    if (longer.length() - shorter.length() > 1) {
        return false;
    }

    bool foundMismatch = false;
    for (size_t si = 0, li = 0; si < shorter.length(); si++, li++) {
        if (shorter[si] != longer[li]) {
            if (foundMismatch) {
                return false;
            }
            foundMismatch = true;
            if (aStr.length() != bStr.length()) {
                // Keep bi at same position while ai moves ahead
                si--;
            }
        }
    }
    return true;
}


void test(std::string aStr, std::string bStr, bool shouldEqual) {
    std::string eqStr = shouldEqual ? "true" : "false";
    if (oneAway(aStr, bStr) != shouldEqual) {
        std::cout << "TEST FAIL v1: [" << aStr << " :: " << bStr << 
            "] should eval to " << eqStr << std::endl;
    }

    if (oneAwayCombined(aStr, bStr) != shouldEqual) {
        std::cout << "TEST FAIL v2: [" << aStr << " :: " << bStr << 
            "] should eval to " << eqStr << std::endl;
    }
}

int main() {
    std::string s1 = "pale";
    std::string s2 = "ple";
    test(s1, s2, true);

    std::string s3 = "pales";
    test(s1, s3, true);
    test(s2, s3, false);

    std::string s4 = "bale";
    test(s1, s4, true);
    test(s2, s4, false);
    test(s3, s4, false);

    std::string s5 = "bake";
    test(s1, s5, false);
    test(s2, s5, false);
    test(s3, s5, false);
    test(s4, s5, true);

    std::string s6 = "bae";
    test(s4, s6, true);
    test(s5, s6, true);

    std::string empty = "";
    test(s1, empty, false);
    test(s3, empty, false);

    std::string s7 = "a";
    test(s1, s7, false);
    test(empty, s7, true);

    std::cout << "Testing complete" << std::endl;
}
