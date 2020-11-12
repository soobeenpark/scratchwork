// https://programmers.co.kr/learn/courses/30/lessons/42898
// Morning Commute

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
vector<vector<int>> cache;
const int MOD = 1000000007;

struct VectorHash {
    size_t operator()(const std::vector<int> &v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
typedef unordered_set<vector<int>, VectorHash> MySet;

int solve(const MySet &pdls, int m, int n) {
    for (int row = 1; row <= m; row++) {
        for (int col = 1; col <= n; col++) {
            if (row == 1 && col == 1) {
                cache[row][col] = 1;
            } else {
                int ans = 0;
                if (pdls.find(vector<int>({row, col})) == pdls.end()) {
                    if (row > 1) {
                        ans += cache[row - 1][col] % MOD;
                    }
                    if (col > 1) {
                        ans += cache[row][col - 1] % MOD;
                    }
                }
                cache[row][col] = ans;
            }
        }
    }
    return cache[m][n] % MOD;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    MySet pdls(puddles.begin(), puddles.end());
    cache = vector<vector<int>>(m + 1);
    for (int i = 0; i <= m; i++) {
        cache[i] = vector<int>(n + 1, 0);
    }

    return solve(pdls, m, n);
}
