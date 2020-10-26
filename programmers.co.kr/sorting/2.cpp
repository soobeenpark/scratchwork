// https://programmers.co.kr/learn/courses/30/lessons/42746
// Biggest Num String

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

bool cmp(const string &a, const string &b) {
    return a + b > b + a;
}

string solution(vector<int> numbers) {
    if (*max_element(numbers.begin(), numbers.end()) == 0) {
        return "0";
    }
    vector<string> numStrings;
    for (int num : numbers) {
        numStrings.push_back(to_string(num));
    }
    sort(numStrings.begin(), numStrings.end(), cmp);

    string answer = "";
    for (string num : numStrings) {
        answer += num;
    }
    return answer;
}
