#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define MAXDEPTH 100001
#define MAXEXP 16
using namespace std;
int N, K, a, b, c;

vector <vector<pair<int,int>> > roads;

int depth[MAXDEPTH] = { -1 };
int ancestor[MAXDEPTH][MAXEXP+1];
int dp[MAXDEPTH][MAXEXP+1][2];

void setTrees(int curr, int parent, int val) {
    dp[curr][0][1] = val;
    dp[curr][0][0] = val;

    depth[curr] = depth[parent] + 1;
    
    ancestor[curr][0] = parent;
    for (int i = 1; i <= MAXEXP; i++) {
        int _next = ancestor[curr][i - 1];
        ancestor[curr][i] = ancestor[_next][i - 1];
    }

    for (int i = 0; i < roads[curr].size(); i++) {
        int _nextIdx = roads[curr][i].first;
        int _nextVal = roads[curr][i].second;
        if (_nextIdx != parent)
            setTrees(_nextIdx, curr, _nextVal);
    }
}

void setDP() {
    for (int jump = 1; jump <= MAXEXP; jump++) {
        for (int curr = 1; curr <= N; curr++) {
            int _next = ancestor[curr][jump - 1];
            dp[curr][jump][1] = max(dp[curr][jump - 1][1], dp[_next][jump - 1][1]);
            dp[curr][jump][0] = min(dp[curr][jump - 1][0], dp[_next][jump - 1][0]);
        }
    }
}

void setEqualDepth(int &start, int &end, int &maxAnswer, int &minAnswer) {
    
    if (depth[start] != depth[end]) {
        
        if (depth[start] > depth[end]) swap(start, end);

        for (int jump = MAXEXP; jump >= 0; jump--) {
            if (depth[start] <= depth[ancestor[end][jump]]) {

                maxAnswer = max(maxAnswer, dp[end][jump][1]);
                minAnswer = min(minAnswer, dp[end][jump][0]);

                end = ancestor[end][jump];
            }
        }
    }
}
void setEqualAncestor(int &LCA, int& start, int& end, int& maxAnswer, int& minAnswer) {
    if (start != end) {

        for (int jump = MAXEXP; jump >= 0; jump--) {
            if (ancestor[start][jump] != ancestor[end][jump]) {

                maxAnswer = max(maxAnswer, max(dp[start][jump][1], dp[end][jump][1]));
                minAnswer = min(minAnswer, min(dp[start][jump][0], dp[end][jump][0]));
                end = ancestor[end][jump];
                start = ancestor[start][jump];
            }
            LCA = ancestor[start][jump];
        }
    }
}

void input_solve(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; roads.resize(N + 1);
    for(int i=0; i<N-1; i++){
        cin >> a >> b >> c;
        roads[a].push_back({ b, c });
        roads[b].push_back({ a, c });
    }
   
    setTrees(1, 0, 0);


    setDP(); 
    cin >> K;
    for(int i=0; i<K; i++){
        int LCA = 0, start, dest;
        int minAnswer = 2147483647, maxAnswer = -2147483648;
        cin >> start >> dest;
        // 1. 깊이를 같도록 맞춰준다.
        
        setEqualDepth(start, dest, maxAnswer, minAnswer);
        // 2. 같은 조상을 만나도록 맞춰준다.
        LCA = start;
        setEqualAncestor(LCA, start, dest, maxAnswer, minAnswer);
        // 3. 결과 경우의 수 2개 중 분류 한다.
        if (start != LCA) {
            maxAnswer = max(maxAnswer, max(dp[start][0][1], dp[dest][0][1]));
            minAnswer = min(minAnswer, min(dp[start][0][0], dp[dest][0][0]));
        }
        cout << minAnswer <<' '<<maxAnswer<<'\n';
    }
}

int main(){
    input_solve();
}