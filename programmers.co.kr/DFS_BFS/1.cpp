// https://programmers.co.kr/learn/courses/30/lessons/43165
// Target Number

#include <string>
#include <vector>

using namespace std;

int search(int k, const vector<int> &numbers, int sum, const int target) {
    if (k == numbers.size()) {
        return (int)(sum == target);
    }
    // Addition case
    int ans = search(k+1, numbers, sum+numbers[k], target);
    ans += search(k+1, numbers, sum-numbers[k], target);
    return ans;
}

int solution(vector<int> numbers, int target) {
    return search(0, numbers, 0, target);
}
