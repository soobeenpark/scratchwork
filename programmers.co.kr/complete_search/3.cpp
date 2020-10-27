// https://programmers.co.kr/learn/courses/30/lessons/42842
// Carpet

#include <cmath>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    int total = brown + yellow;
    vector<int> answer;

    bool found = false;
    for (int vert = 3; !found && vert <= sqrt(total); vert++) {
        if (total % vert == 0) {
            int horz = total / vert;
            if ((vert - 2) * (horz - 2) == yellow) {
                answer.push_back(horz);
                answer.push_back(vert);
                found = true;
            }
        }
    }
    return answer;
}
