#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int N, M, roomCnt, answer;
vector <vector<int>> cows;
vector <vector<int>> graphs;
vector <vector<int>> capacity;
vector <vector<int>> flow;
vector <int> rooms;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M; cows.resize(N+1); rooms.resize(M+1);
    capacity.resize(N+M+2); for(auto &c : capacity) c.resize(N+M+2);
    flow.resize(N+M+2); for(auto &f : flow) f.resize(N+M+2);
    graphs.resize(N+M+2);
    for(int i=1; i<=N; i++){
        cin >> roomCnt; cows[i].resize(roomCnt);
        for(int r=0; r<roomCnt; r++){
            cin >> cows[i][r];
        }
    }
}
void graphModeling(){
    // 축사의 index는 소(N) 뒤 부
    for(int i=1; i<=M; i++){
        graphs[0].push_back(i+N);
        graphs[i+N].push_back(0);
        capacity[0][i+N] = 1;
    }
    for(int i=1; i<=N; i++){
        graphs[N+M+1].push_back(i);
        graphs[i].push_back(N+M+1);
        capacity[i][N+M+1] = 1;
    }
    for(int cowNum=1; cowNum<=N; cowNum++){
        for(auto &room : cows[cowNum]){
            graphs[room+N].push_back(cowNum);
            graphs[cowNum].push_back(room+N);
            capacity[room+N][cowNum] = 1;
        }
    }
}
void NetworkFlow(){
    while(1){
        vector <int> prev(N+M+2, -1);
        queue <int> q;
        q.push(0);

        while(q.size()){
            int curr = q.front(); q.pop();
            for(auto &next : graphs[curr]){
                if(prev[next] != -1 )continue;

                if(capacity[curr][next] > flow[curr][next]){
                    prev[next] = curr;
                    q.push(next);
                    if(next == N+M+1) break;
                }
            }
        }
        if(prev[N+M+1] == -1) break;

        int minFlow = 2147483647;
        for(int i=N+M+1 ; i!=0; i=prev[i]){
            minFlow = min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i]);
        }
        for(int i=N+M+1; i != 0; i=prev[i]){
            flow[prev[i]][i] += 1;
            flow[i][prev[i]] -= 1;
        }
    }
    for(int i=1; i<=M; i++){
        for(int j=1; j<=N; j++){
            if(flow[i+N][j]){
                answer++;
            }
        }
    }
    cout << answer;
}
int main(){
    input();
    graphModeling();
    NetworkFlow();
}