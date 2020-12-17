#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX = 100;
int n;
string guesses[MAX];
int strikes[MAX], balls[MAX];

pair<int, int> check_guess_to_target(string target, string guess) {
    int strike = 0;
    int ball = 0;
    for (size_t i = 0; i < target.size(); i++) {
        for (size_t j = 0; j < guess.size(); j++) {
            if (target[i] == guess[j]) {
                strike += (i == j);
                ball += (i != j);
            }
        }
    }
    return {strike, ball};
}

bool check_guesses(string target) {
    // go through each guesses and see if they match
    for (int i = 0; i < n; i++) {
        pair<int, int> strike_ball = check_guess_to_target(target, guesses[i]); 
        int strike = strike_ball.first;
        int ball = strike_ball.second;
        if (strike != strikes[i] || ball != balls[i]) {
            return false;
        }
    }
    // all guesses must match the strike and ball numbers for valid target
    return true;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> guesses[i];
        cin >> strikes[i] >> balls[i];
    }

    int ans = 0;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            for (int k = 1; k < 10; k++) {
                if (i != j && i !=k && j != k) {
                    string target = to_string(i) + to_string(j) + to_string(k);
                    ans += check_guesses(target);
                }
            }
        }
    }
    cout << ans << endl;
}
