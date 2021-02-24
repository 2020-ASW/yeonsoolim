#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define ll long long
#define INF 2147483647
using namespace std;
vector <vector<ll>> dp;
void Floyd_Warshall(int n, vector<vector<int>> fares){
    dp.resize(n+1); for(auto &d: dp) d.resize(n+1);
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) dp[i][j] = INF;
    for(int i=1; i<=n; i++) dp[i][i] = 0;
    for(auto &fare : fares){
        int a = fare[0], b = fare[1], c = fare[2];
        dp[a][b] = c;
        dp[b][a] = c;
    }
    for(int k=1; k<=n; k++){
        for(int left = 1; left <= n; left ++){
            for(int right = 1; right <= n; right++){
                dp[left][right] = min(dp[left][right], dp[left][k] + dp[k][right]);
            }
        }
    }

}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    Floyd_Warshall(n, fares);

    // s -> ? -> a -> b
    // s -> ? -> b -> a
    // s -> a -> b
    // s -> b -> a
    // s -> a,b
    ll answer = INF;
    //ll case5 = dp[s][a] + dp[s][b];
    //answer = min(answer, case5);
    //ll case4 = dp[s][b] + dp[b][a];
    //ll case3 = dp[s][a] + dp[a][b];
    for(int k=1; k<=n; k++){
        //if(k==s continue);
        answer = min(answer, dp[s][k] + dp[k][a] + dp[k][b]);
        answer = min(answer, dp[s][k] + dp[k][b] + dp[k][a]);
    }

    return answer;
}