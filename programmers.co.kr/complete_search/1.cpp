// https://programmers.co.kr/learn/courses/30/lessons/42840
// Mock Exam

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isCorrect(int qNum, const vector<int> &answers,
               const vector<int> &pattern) {
    return answers[qNum] == pattern[qNum % pattern.size()];
}

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> pattern1({1, 2, 3, 4, 5});
    vector<int> pattern2({2, 1, 2, 3, 2, 4, 2, 5});
    vector<int> pattern3({3, 3, 1, 1, 2, 2, 4, 4, 5, 5});

    vector<int> numCorrect(3, 0);
    for (int i = 0; i < answers.size(); i++) {
        numCorrect[0] += isCorrect(i, answers, pattern1);
        numCorrect[1] += isCorrect(i, answers, pattern2);
        numCorrect[2] += isCorrect(i, answers, pattern3);
    }
    int max = *max_element(numCorrect.begin(), numCorrect.end());

    for (int i = 0; i < numCorrect.size(); i++) {
        if (numCorrect[i] == max) {
            answer.push_back(i + 1);
        }
    }
    return answer;
}
