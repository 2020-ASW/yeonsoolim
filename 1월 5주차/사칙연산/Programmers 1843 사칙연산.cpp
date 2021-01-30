#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[101][101][2];
void init(vector<string>& arr) {
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            dp[i][j][1] = -100000;
            dp[i][j][0] = 100000;
        }
    }
    for (int i = 0; i < arr.size() / 2 + 1; i++) dp[i][i][0] = dp[i][i][1] = stoi(arr[i * 2]);
}
void DP(vector<string>& arr) {
    for (int pos = 1; pos < arr.size() / 2 + 1; pos++) {  //간격
        for (int left = 0; left < arr.size() / 2 + 1 - pos; left++) {
            int right = left + pos;
            for (int k = left; k < right; k++) {
                if (arr[k * 2 + 1] == "+") {
                    // + 일때  최대 : 최대 + 최대  최소 : 최소 + 최소
                    dp[left][right][1] = max(dp[left][k][1] + dp[k + 1][right][1], dp[left][right][1]);
                    dp[left][right][0] = min(dp[left][k][0] + dp[k + 1][right][0], dp[left][right][0]);

                }
                else {
                    // - 일때  최대 : 최대 - 최소  최소 : 최소 - 최대
                    dp[left][right][1] = max(dp[left][k][1] - dp[k + 1][right][0], dp[left][right][1]);
                    dp[left][right][0] = min(dp[left][k][0] - dp[k + 1][right][1], dp[left][right][0]);

                }
            }
        }
    }
}
int solution(vector<string> arr)
{

    init(arr);
    DP(arr);

    return dp[0][arr.size() / 2][1];
}