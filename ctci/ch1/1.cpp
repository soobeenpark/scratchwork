#include <iostream>
#include <unordered_set>
#include <string>

/* Use a set to store characters.
 * Lookup time for each character in set is O(1).
 *
 * Time: O(min(n,c)), where n is length of string, c is charset size.
 * Space: O(c)
 */

const size_t CHARSET_SIZE = 128; // Following ASCII convention

bool isUniqueChars(std::string s) {
    if (s.length() > CHARSET_SIZE) {
        return false;
    }

    std::unordered_set<char> set;
    for (size_t i = 0; i < s.length(); i++) {
        if (set.find(s[i]) == set.cend()) {
            // Not found in set
            set.insert(s[i]);
        } else {
            // Found in set -- not unique
            return false;
        }
    }
    return true;
}

int main() {
    std::string a = "abcdefg";
    if (!isUniqueChars(a)) {
        std::cout << "Test 1 FAIL" << std::endl;
    }

    std::string b = "abcdefb";
    if (isUniqueChars(b)) {
        std::cout << "Test 2 FAIL" << std::endl;
    }

    std::string empty = "";
    if (!isUniqueChars(empty)) {
        std::cout << "Test 3 FAIL" << std::endl;
    }

    std::cout << "Tests finished" << std::endl;
}
