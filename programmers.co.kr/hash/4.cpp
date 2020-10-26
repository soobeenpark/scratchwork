// https://programmers.co.kr/learn/courses/30/lessons/42579

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    map<string, int> genreTotal;
    for (size_t i = 0; i < genres.size(); ++i) {
        genreTotal[genres[i]] += plays[i];
    }

    vector<tuple<int, int, int, string>> totalsPlaysIds;
    for (int i = 0; i < genres.size(); ++i) {
        tuple<int, int, int, string> ins =
            make_tuple(-genreTotal[genres[i]], -plays[i], i, genres[i]);
        totalsPlaysIds.push_back(ins);
    }

    sort(totalsPlaysIds.begin(), totalsPlaysIds.end());

    unordered_map<string, int> genreCount;
    vector<int> answer;
    for (tuple<int, int, int, string> song : totalsPlaysIds) {
        string genre = get<3>(song);
        if (genreCount[genre] < 2) {
            answer.push_back(get<2>(song));
        }
        genreCount[genre]++;
    }

    return answer;
}
