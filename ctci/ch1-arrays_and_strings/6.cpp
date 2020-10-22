#include <iostream>
#include <sstream>

/* Let n be the length of the src string.
 * Time: O(n)
 * Space: O(n)
 *
 * Note that C++ stringstream's don't suffer from the O(k^2) complexity
 * described in CTCI that the Java String class does, since string concatenation
 * is done in linear time in C++.
 */
std::string compress_v1(std::string src) {
    std::stringstream ss;
    size_t count = 0;
    for (size_t i = 0; i < src.length(); ++i) {
        count++;
        if (i+1 == src.length() || src[i+1] != src[i]) {
            ss << src[i];
            ss << count;
            count = 0; // Reset count since tracking character was reset.
        }
    }

    // Only return if the "compressed" string is shorter than the src string.
    std::string ret = ss.str();
    return ret.length() < src.length() ? ret : src;
}


// Helper for v2
size_t compressedLength(std::string src) {
    size_t ret = 0;
    size_t count = 0;
    for (size_t i = 0; i < src.length(); ++i) {
        count++;
        if (i+1 == src.length() || src[i] != src[i+1]) {
            ret += 1 + std::to_string(count).length();
            count = 0;
        }
    }
    return ret;
}

/* Same as v1, but small change to calculate upfront whether compression
 * will result in smaller string than src, and return immediately if not.
 * This will save time and space for highly non-repeating strings, but the
 * tradeoff is that this creates a second loop where potentially more work is
 * done for strings that need compression.
 *
 * Let n be the length of the string.
 * Time: O(n)
 * Space: (O(n)
 */
std::string compress_v2(std::string src) {
    if (compressedLength(src) >= src.length()) {
        return src;
    }

    std::stringstream ss;
    size_t count = 0;
    for (size_t i = 0; i < src.length(); ++i) {
        count++;
        if (i+1 == src.length() || src[i+1] != src[i]) {
            ss << src[i];
            ss << count;
            count = 0; // Reset count since tracking character was reset.
        }
    }

    return ss.str();
}


void test(std::string src, std::string target) {
    if (compress_v1(src) != target) {
        std::cout << "TEST FAIL v1: " << compress_v1(src) << " should equal " << target << std::endl;
    }

    if (compress_v2(src) != target) {
        std::cout << "TEST FAIL v2: " << compress_v2(src) << " should equal " << target << std::endl;
    }
}

int main() {
    std::string s1 = "aabcccccaaa";
    std::string s1Target = "a2b1c5a3";
    test(s1, s1Target);

    std::string s2 = "abcd";
    std::string s2Target = s2;
    test(s2, s2Target);

    std::string s3 = "abdd";
    std::string s3Target = s3;
    test(s3, s3Target);

    std::string s4 = "aaaa";
    std::string s4Target = "a4";
    test(s4, s4Target);

    std::string s5 = "aabbb";
    std::string s5Target = "a2b3";
    test(s5, s5Target);

    std::cout << "Testing complete" << std::endl;
}
