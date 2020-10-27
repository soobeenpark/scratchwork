// https://programmers.co.kr/learn/courses/30/lessons/42839
// Finding Primes

#include <cmath>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// pre: num is a nonnegative integer
bool isPrime(int num) {
    if (num == 2) {
        return true;
    } else if (num == 0 || num == 1 || num % 2 == 0) {
        return false;
    }

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int searchAll(const string &numbers, string &builder, int index,
              unordered_set<int> &seen) {
    if (index == numbers.length()) {
        if (builder.empty() || seen.find(stoi(builder)) != seen.end()) {
            return 0;
        }
        int check = stoi(builder);
        seen.insert(check);
        return isPrime(check);
    }
    // Generate subset with index num excluded
    int result = searchAll(numbers, builder, index + 1, seen);
    // Generate subset with index num included, all permutations
    for (int i = 0; i <= builder.length(); i++) {
        char toInsert = numbers[index];
        builder = builder.substr(0, i) + toInsert + builder.substr(i);
        result += searchAll(numbers, builder, index + 1, seen);
        builder = builder.substr(0, i) + builder.substr(i + 1);
    }
    return result;
}

int solution(string numbers) {
    string builder = "";
    unordered_set<int> seen;
    int answer = searchAll(numbers, builder, 0, seen);
    return answer;
}
