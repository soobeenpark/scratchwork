// https://programmers.co.kr/learn/courses/30/lessons/43105
// Integer Triangle

#include <algorithm>
#include <string>
#include <vector>

using namespace std;
vector<vector<int>> cache;

int solution(vector<vector<int>> triangle) {
    // Initialize cache
    cache = vector<vector<int>>(triangle.size());
    for (int i = 0; i < triangle.size(); i++) {
        cache[i].resize(triangle[i].size());
    }

    // DP
    cache[0][0] = triangle[0][0];
    for (int i = 1; i < triangle.size(); i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                cache[i][j] = triangle[i][j] + cache[i - 1][j];
            } else if (j == i) {
                cache[i][j] = triangle[i][j] + cache[i - 1][j - 1];
            } else {
                cache[i][j] =
                    triangle[i][j] + max(cache[i - 1][j - 1], cache[i - 1][j]);
            }
        }
    }
    vector<int> lastRow = cache[cache.size() - 1];
    return *max_element(lastRow.begin(), lastRow.end());
}
