#include <iostream>
#include <algorithm>
#include <vector>
#define INF 10000000
#define mINF -10000000
using namespace std;
struct  MUNG{
    int val;
    int idx;
};
vector <MUNG> mungmunge;
vector <vector<int>> roads_monkey;
vector <vector<int>> roads_dog;
int N, M, Q, a, b, c;
bool cmp(const MUNG &a, const MUNG &b){
    return a.val < b.val;
}
void Floyd_Warshall(){
    for(int m=1; m<=N; m++){
        int k= mungmunge[m].idx;
        for(int i=1; i<=N; i++){
            for(int j=1 ;j<=N; j++){

                if(roads_monkey[i][j] + roads_dog[i][j] > roads_monkey[i][k] + roads_monkey[k][j] + max(roads_dog[i][k],roads_dog[k][j])){
                    roads_monkey[i][j] = roads_monkey[i][k] + roads_monkey[k][j];
                    roads_dog[i][j] = max(roads_dog[i][k],roads_dog[k][j]);
                }
            }
        }
    }
}

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q; mungmunge.resize(N+1);
    roads_monkey.resize(N+1); for(auto &road : roads_monkey) road.resize(N+1);
    roads_dog.resize(N+1); for(auto &road : roads_dog) road.resize(N+1);
    for(int i=1; i<=N; i++) {
        int temp;
        cin >> temp;
        mungmunge[i] = {temp, i};
        roads_monkey[i][i] = 0;
        roads_dog[i][i] = mungmunge[i].val;
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            roads_monkey[i][j] = INF;
            roads_dog[i][j] = max(mungmunge[i].val, mungmunge[j].val);
        }
    }
    for(int i=1; i<=M; i++) {
        cin >> a >> b >> c;
        roads_dog[a][b] = max(mungmunge[a].val, mungmunge[b].val);
        roads_monkey[a][b] = roads_monkey[b][a] = c;
    }
    sort(mungmunge.begin(), mungmunge.end(), cmp);

    Floyd_Warshall();

    for(int i=1; i<=Q; i++){
        cin >> a >> b;
        cout << (roads_monkey[a][b] == INF? -1 : roads_monkey[a][b] + roads_dog[a][b])<<'\n';
    }
}
int main(){
    input();
}