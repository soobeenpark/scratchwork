// https://programmers.co.kr/learn/courses/30/lessons/42748
// Kth Number

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int extract(vector<int> array, vector<int> cmd) {
    vector<int> temp(array.begin() + cmd[0] - 1, array.begin() + cmd[1]);
    sort(temp.begin(), temp.end());
    return temp[cmd[2] - 1];
}

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    transform(commands.begin(), commands.end(), back_inserter(answer),
              [=](vector<int> cmd) { return extract(array, cmd); });
    return answer;
}
