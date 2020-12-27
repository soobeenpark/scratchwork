#include <bits/stdc++.h>
using namespace std;

class Times {
public:
    int begin;
    int end;

    Times() {}
    Times(int b, int e) : begin(b), end(e) {}
};

bool sort_cmp(const Times &t1, const Times &t2) {
    return t1.begin < t2.begin;
}

typedef priority_queue<int, std::vector<int>, std::greater<int>> pq_t;

int main() {
    int n;
    cin >> n;

    // Get all lectures into array
    Times lecturesArr[200001];
    for (int i = 0; i < n; i++) {
        int begin, end;
        cin >> begin >> end;
        lecturesArr[i] = Times(begin, end);
    }

    // Sort lectures by ascending begin time
    sort(lecturesArr, lecturesArr + n, sort_cmp);

    // Iterate through all lectures, maintaining currently held lecture end times in pq
    pq_t currentLecsEnd;
    for (int i = 0; i < n; i++) {
        int begin = lecturesArr[i].begin;
        if (!currentLecsEnd.empty() && currentLecsEnd.top() <= begin) {
            // if we can reuse finished classroom, return the classroom
            currentLecsEnd.pop();
        }
        // Add a new lecture classroom for the current lecture
        currentLecsEnd.push(lecturesArr[i].end);
    }
    cout << currentLecsEnd.size() << endl;
}
