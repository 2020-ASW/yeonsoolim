#include <iostream>
#include <vector>
#include <algorithm>
#define INF 100000

using namespace std;
vector <vector<int>> roads;
int N;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; roads.resize(N+1); for(auto &road : roads) road.resize(N+1);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> roads[i][j];
        }
    }
}
int floyd_warshall(){
    int result = 0;
    int result1= 0;
    vector<vector<bool>> notNeed;
    notNeed.resize(N+1); for(auto &tmp : notNeed) tmp.resize(N+1);

    for(int k=1; k<=N; k++){
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(k==i || k==j) continue;
                if(roads[i][k] + roads[k][j] < roads[i][j]) return -1;
                if(roads[i][k] + roads[k][j] == roads[i][j]) {
                    notNeed[i][j] = true;
                }
            }
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(!notNeed[i][j]) result += roads[i][j];
        }
    }
    return (int)result/2;
}
int main(){
    input();
    cout << floyd_warshall();
}