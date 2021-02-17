#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
struct Person{
    int cost;
    int boss;
    int idx;
};
int totalTeam;
int dp[300001][2];
unordered_map <int, vector<Person>> boss;
unordered_map <int, int> underling;
void treeSetting(vector <int> &sales, vector <vector<int> > &links){
    boss[0].push_back({0, 0, 1});  //cost 0 boss 0  CEO
    for(auto &link : links){
        boss[link[0]].push_back({sales[link[1]-1], link[0], link[1]});
        underling[link[1]] = link[0];
    }
    totalTeam = boss.size();
}

void search(vector <int> &sales, int idx){
    if(boss.find(idx) == boss.end()){  // leaf Node
        // cout << "\"" <<idx<<"\"" <<' '<<sales[idx-1]<<'\n';
        dp[idx][1] = sales[idx-1];
        dp[idx][0] = 0;
        return;
    }
    for(auto &next : boss[idx]){
        search(sales, next.idx);// 안방문
    }
    //0일때 -> 자식만 2팀 커버 가능.

    dp[idx][1] = min(dp[boss[idx][0].idx][0], dp[boss[idx][0].idx][1]);
    //dp[idx][0] = dp[boss[idx][0].idx][1];

    bool pick = false;
    int diff = min(987654321,dp[boss[idx][0].idx][1]-dp[boss[idx][0].idx][0]);
    // cout << dp[idx][0]<<" "<<boss[idx].size()<<' ' <<fromUnderling<<'\n';
    for(int i=1; i<boss[idx].size(); i++){
        //dp[idx][1] = min(dp[idx][1], min(dp[idx][1]+dp[boss[idx][i].idx][0], dp[idx][1]+dp[boss[idx][i].idx][1]));
        dp[idx][1] += min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
        //  dp[idx][0] += min(dp[idx][0], dp[boss[idx][i].idx][1]);
        //if(dp[boss[idx][i].idx][1] != 0 && dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
        //     pick = true;
        // }
        if(dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
            pick = true;
        }
        diff = min(diff, dp[boss[idx][i].idx][1]-dp[boss[idx][i].idx][0]);

        //dp[idx][0] += dp[boss[idx][i].idx][1];
    }
    if(pick) dp[idx][0] = dp[idx][1];
    else dp[idx][0] = diff + dp[idx][1];

    dp[idx][1] += sales[idx-1];

    // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';

    //dp[idx][1] += fromUnderling;
    //dp[idx][0] = fromUnderling == 0 ? dp[idx][0] : fromUnderling;
    // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';
}
void print(int curr){
    for(auto &next : boss[curr]){
        cout << next.idx <<" : "<<dp[next.idx][0]<<' '<<dp[next.idx][1]<<'\n';
        print(next.idx);
    }
}
int solution(vector<int> sales, vector<vector<int>> links) {
    treeSetting(sales, links);
    search(sales, 0);

    //int curr = 1;
    //print(1);

    // cout << dp[0][0]<<','<<dp[0][1]<<'\n';
    // cout << dp[1][0]<<','<<dp[1][1]<<'\n';
    return min(dp[1][0], dp[1][1]);
}