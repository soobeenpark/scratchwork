// https://programmers.co.kr/learn/courses/30/lessons/43164
// Travel Path

#include <algorithm>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string START = "ICN";

// each node in dst_list will hold the destination city name and whether visited
// or not
typedef list<pair<string, bool>> dst_list;

class Solver {
  private:
    vector<vector<string>> tickets;
    vector<string> answer;
    unordered_map<string, dst_list> adjList;

    // Initialize adjacency list
    void initAdjList() {
        for (vector<string> ticket : tickets) {
            string src = ticket[0];
            string dst = ticket[1];
            adjList[src].push_back(make_pair(dst, false));
        }
    }

    // Goes through and sorts each list in adj list
    void sortAdjList() {
        for (auto it = adjList.begin(); it != adjList.end(); it++) {
            it->second.sort();
        }
    }

    // The recursive backtracking DFS solver
    bool visitCountries(string src, int depth) {
        answer.push_back(src);
        if (depth == tickets.size()) {
            // We've reached our end point - no more to travel
            return true;
        }

        dst_list &dests = adjList[src];
        for (auto it = dests.begin(); it != dests.end(); it++) {
            if (!it->second) {
                // recursive backtracking
                it->second = true;
                if (visitCountries(it->first, depth + 1)) {
                    return true;
                }
                it->second = false;
            }
        }

        // Reached end - no cities were successful
        answer.pop_back();
        return false;
    }

  public:
    // Constructor
    Solver(vector<vector<string>> tickets)
        : tickets(tickets), answer(), adjList() {}

    // Driver
    vector<string> solve() {
        initAdjList();
        sortAdjList();
        visitCountries(START, 0);
        return answer;
    }
};

// Entry point
vector<string> solution(vector<vector<string>> tickets) {
    Solver s = Solver(tickets);
    return s.solve();
}
