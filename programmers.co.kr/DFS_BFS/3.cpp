// https://programmers.co.kr/learn/courses/30/lessons/43163
// Changing Words

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool isOneLetterApart(string a, string b) {
    int mismatches = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            mismatches++;
        }
        if (mismatches >= 2) {
            return false;
        }
    }
    return (mismatches == 1);
}

int BFS(string begin, string target, const vector<string> &words) {
    queue<pair<string, int>> q;
    q.push(make_pair(begin, 0));
    unordered_set<string> visited;
    visited.insert(begin);

    while (!q.empty()) {
        pair<string, int> node = q.front();
        q.pop();
        string word = node.first;
        int BFSLevel = node.second;

        if (word == target) {
            return BFSLevel;
        }
        for (int i = 0; i < words.size(); i++) {
            if (isOneLetterApart(word, words[i]) &&
                visited.find(words[i]) == visited.end()) {
                visited.insert(words[i]);
                q.push(make_pair(words[i], BFSLevel + 1));
            }
        }
    }
    return 0;
}

int solution(string begin, string target, vector<string> words) {
    if (find(words.begin(), words.end(), target) == words.end()) {
        return 0;
    }
    return BFS(begin, target, words);
}
