#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;
struct weightValue{
    int weight;
    int value;
};
vector <weightValue> items;
vector <vector <int> > dp;
int N, K, w, v;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    dp.resize(N); for(auto &d: dp) d.resize(K+1);
    for(int i=0; i<N; i++){
        cin >> w >> v;
        items.push_back({w,v});
    }
}
void makeDP(){
    for(int j=0; j<=K; j++){
        if(items[0].weight > j) dp[0][j] = 0;
        else dp[0][j] = items[0].value;
    }
    for(int i=1; i<N; i++){
        for(int j=0; j<=K; j++){
            // i : item의 Index
            // j : 현재 가방 무게
            if(items[i].weight > j) dp[i][j] = dp[i-1][j];
            // 넣고도 남는 자리가 있을 수 있다.   j-items[i].weight => 남는 무게 중 가장 큰
            else dp[i][j] = max(dp[i-1][j], items[i].value +  dp[i-1][j-items[i].weight]);
        }
    }
}
void getMax(){
//    int answer = 0;
//    for(int i=0; i<N; i++) answer = max(answer, dp[i][K]);
//    cout << answer;
    cout << dp[N-1][K];
}
int main(){
    input();
    makeDP();
    getMax();
}