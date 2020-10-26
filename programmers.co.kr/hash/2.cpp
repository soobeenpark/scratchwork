// https://programmers.co.kr/learn/courses/30/lessons/42577
// Phonebook

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool solution(vector<string> phone_book) {
    unordered_map<string, int> map;
    for (string phoneNum : phone_book) {
        map[phoneNum]++;
    }
    for (string phoneNum : phone_book) {
        for (size_t i = 1; i < phoneNum.length(); i++) {
            string sub = phoneNum.substr(0, i);
            if (map.find(sub) != map.end()) {
                return false;
            }
        }
    }
    return true;
}
