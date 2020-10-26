#include <bitset>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

const int CHARSET_SIZE = 26;

/* Recursion version
 *
 * Let n be the length of the string.
 * If n is even length string:
 * First recursive call: (n-1) comparisons + (n-2) substring creation
 * Next recursive call: (n-3) comparisons + (n-4) substring creation
 * Next recursive call: (n-5) comparisons + (n-6) substring creation
 * ...
 * Next recursive call: 1 comparison
 * Final recursive call: constant time (base case)
 *
 * There are n/2 recursive calls in worst case.
 * The series sums up to O(n^2) runtime.
 * Odd-length string follows similar logic.
 *
 * Time: O(n^2)
 * Space: O(n^2)
 */
bool palindromePermutation_v1(std::string s) {
    if (s.length() == 0 || s.length() == 1) {
        return true;
    }

    char firstLetter = s[0];
    size_t foundIndex = 0;
    // Find matching character pair
    for (size_t i = 1; foundIndex == 0 && i < s.length(); i++) {
        if (s[i] == firstLetter) {
            foundIndex = i;
        }
    }

    std::string substring;
    if (foundIndex == 0) { // Pair not found
        if (s.length() % 2 == 0) {
            // Single non-matching char can only be in palindrome if string is
            // even length.
            return false;
        } else {
            substring = s.substr(1);
        }
    } else {
        substring = s.substr(1, foundIndex - 1) + s.substr(foundIndex + 1);
    }

    return palindromePermutation_v1(substring);
}

/* Hash Table implementation - two passes.
 *
 * Let n be the length of the string.
 * Time: O(n)
 * Space: O(n)
 */
bool palindromePermutation_v2(std::string s) {
    // Create counter dict of each character in string
    std::unordered_map<char, size_t> map;
    for (char c : s) {
        map[c]++;
    }

    // A palindrome must have all even number of counts, with the one exception
    // that exactly one character count can be odd iff the string is of odd
    // length.
    bool oddCountEncountered = false;
    std::unordered_map<char, size_t>::iterator iter;
    for (iter = map.begin(); iter != map.end(); ++iter) {
        if (oddCountEncountered && iter->second % 2 == 1) {
            return false;
        }

        if (iter->second % 2 == 1) {
            assert(!oddCountEncountered);
            oddCountEncountered = true;
        }
    }
    return true;
}

/* Hash Table implementation - one pass.
 *
 * As noted in CTCI, not necessarily more optimal than v2.
 *
 * Let n be the length of the string.
 * Time: O(n)
 * Space: O(n)
 */
bool palindromePermutation_v3(std::string s) {
    std::unordered_map<char, size_t> map;
    size_t oddCount = 0; // Number of keys with odd values in hash table
    for (char c : s) {
        map[c]++;
        if (map[c] % 2 == 1) {
            oddCount++;
        } else {
            assert(oddCount > 0);
            oddCount--;
        }
    }
    return oddCount <= 1;
}

/* Bitset implementation of version3, uses less memory and faster using bitwise
 * operations.
 *
 * We assume that the charset size of string is equal to CHARSET_SIZE.
 *
 * Let n be the length of the string.
 * Time: O(n)
 * Space: O(n)
 */
bool palindromePermutation_v4(std::string s) {
    std::bitset<CHARSET_SIZE> flags;
    for (char c : s) {
        int index = c - 'a'; // We assume that we are working with lowercase
                             // alphabetic chars.

        // Toggle the bitset index to on/off to keep track if character count is
        // even/odd.
        if (flags[index]) {
            flags[index] = 0;
        } else {
            flags[index] = 1;
        }
    }

    // At maximum, only character count can be odd.
    return flags.count() <= 1;
}

void test(std::string s, bool shouldEqual) {
    std::string eqStr = shouldEqual ? "true" : "false";
    if (palindromePermutation_v1(s) != shouldEqual) {
        std::cout << "TEST FAIL - v1: " << s << " should eval to " << eqStr
                  << std::endl;
    }

    if (palindromePermutation_v2(s) != shouldEqual) {
        std::cout << "TEST FAIL - v2: " << s << " should eval to " << eqStr
                  << std::endl;
    }

    if (palindromePermutation_v3(s) != shouldEqual) {
        std::cout << "TEST FAIL - v3: " << s << " should eval to " << eqStr
                  << std::endl;
    }

    if (palindromePermutation_v4(s) != shouldEqual) {
        std::cout << "TEST FAIL - v4: " << s << " should eval to " << eqStr
                  << std::endl;
    }
}

int main() {
    std::string s1 = "carrace";
    test(s1, true);

    std::string s2 = "tactcoa";
    test(s2, true);

    std::string s3 = "daily";
    test(s3, false);

    std::string s4 = "haha";
    test(s4, true);

    std::string s5 = "hahha";
    test(s5, true);

    std::string s6 = "hahhaa";
    test(s6, false);

    std::string empty = "";
    test(empty, true);

    std::string oneChar = "a";
    test(oneChar, true);

    std::cout << "Tests finished" << std::endl;
}
