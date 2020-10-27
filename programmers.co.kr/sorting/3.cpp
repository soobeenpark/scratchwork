// https://programmers.co.kr/learn/courses/30/lessons/42747
// H-Index

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());

    int i = 0;
    while (i < citations.size()) {
        if (citations[i] <= i) {
            return i;
        }
        i++;
    }
    return i;
}
