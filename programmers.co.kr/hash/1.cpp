// https://programmers.co.kr/learn/courses/30/lessons/42576

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string, int> map;
    for (string name : participant) {
        map[name]++;
    }
    for (string name : completion) {
        map[name]--;
        if (map[name] == 0) {
            map.erase(name);
        }
    }
    return map.begin()->first;
}
