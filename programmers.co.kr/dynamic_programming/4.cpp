// https://programmers.co.kr/learn/courses/30/lessons/42897
// Robbing Houses

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> money) {
    // Robbing first house and not last house
    int house1 = 0;
    int house2 = 0;
    for (int i = 0; i < money.size() - 1; i++) {
        int temp = max(money[i] + house1, house2);
        house1 = house2;
        house2 = temp;
    }
    int ans1 = house2;

    // Robbing last house and not first house
    house1 = 0;
    house2 = 0;
    for (int i = 1; i < money.size(); i++) {
        int temp = max(money[i] + house1, house2);
        house1 = house2;
        house2 = temp;
    }
    int ans2 = house2;

    return max(ans1, ans2);
}
