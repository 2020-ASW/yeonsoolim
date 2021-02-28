# 2188_축사 배정

# NetworkFlow

# Problem

## 문제

농부 존은 소 축사를 완성하였다. 축사 환경을 쾌적하게 유지하기 위해서, 존은 축사를 M개의 칸으로 구분하고, 한 칸에는 최대 한 마리의 소만 들어가게 계획했다.

첫 주에는 소를 임의 배정해서 축사를 운영했으나, 곧 문제가 발생하게 되었다. 바로 소가 자신이 희망하는 몇 개의 축사 외에는 들어가기를 거부하는 것이다.

농부 존을 도와 최대한 많은 수의 소가 축사에 들어갈 수 있도록 하는 프로그램을 작성하시오. 축사의 번호는 1부터 M까지 매겨져 있다.

# Solve

![2188_%E1%84%8E%E1%85%AE%E1%86%A8%E1%84%89%E1%85%A1%20%E1%84%87%E1%85%A2%E1%84%8C%E1%85%A5%E1%86%BC%20ff332b10ead541ec93d46a2f1ce1f3fe/Untitled.png](2188_%E1%84%8E%E1%85%AE%E1%86%A8%E1%84%89%E1%85%A1%20%E1%84%87%E1%85%A2%E1%84%8C%E1%85%A5%E1%86%BC%20ff332b10ead541ec93d46a2f1ce1f3fe/Untitled.png)

- 축사에 대한 소의 연결을 한 모델링을 해준다.

# Code

```cpp
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
```

![2188_%E1%84%8E%E1%85%AE%E1%86%A8%E1%84%89%E1%85%A1%20%E1%84%87%E1%85%A2%E1%84%8C%E1%85%A5%E1%86%BC%20ff332b10ead541ec93d46a2f1ce1f3fe/Untitled%201.png](2188_%E1%84%8E%E1%85%AE%E1%86%A8%E1%84%89%E1%85%A1%20%E1%84%87%E1%85%A2%E1%84%8C%E1%85%A5%E1%86%BC%20ff332b10ead541ec93d46a2f1ce1f3fe/Untitled%201.png)