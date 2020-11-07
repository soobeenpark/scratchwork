#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll solution(int n, vector<int> times) {
    // Sort for bin search to be used later
    sort(times.begin(), times.end());
    ll min = 0;
    ll max = n * (ll)times[times.size() - 1];
    ll answer;

    while (min < max) {
        ll mid = min + (max - min) / 2;
        ll sum = 0;
        for (ll t : times) {
            sum += mid / t;
        }

        if (sum < n) {
            // Not possible - move up min
            min = mid + 1;
        } else {
            // Record answer and optimize for lower upper-bound
            answer = mid;
            max = mid;
        }
    }
    return answer;
}
