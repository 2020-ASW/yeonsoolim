# 1960_행렬 만들기

# NetworkFlow

# Problem

## 문제

n*n 크기의 행렬이 있다. 이 행렬은 0과 1로 이루어 져 있다. 예를 들어 다음과 같은 행렬이 있다고 하자.

![1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled.png](1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled.png)

1행에 1이 2개

2행에 1이 3개

3행에 1이 1개

4행에 1이 1개

1열에 1이 2개

2열에 1이 2개

3열에 1이 2개

4열에 1이 1개

그런데 행렬이 그려진 종이를 잃어버리고 말았다. 그래서 행렬에 대한 자세한 정보는 잃어버렸고 각 행과 열에 있는 1의 개수만을 알고 있다. 위 예에는 1행에는 1이 두 개, 2행에는 3개, 3행에 1개, 4행에 1개, 그리고 1열에 2개, 2열에 2개, 3열에 2개, 4열에 1개가 있는 것이다. 이와 같은 데이터가 주어져 있을 때, 원래의 행렬을 만드는 프로그램을 작성하시오.

# Solve

![1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled%201.png](1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled%201.png)

모든 행,열에 제한되어 있는 1의 갯수에 따라 서로 다른 행,열에 영향을 끼칠 수 있다.

모델링을 모든 행 < - > 열 로 해주고, Source → 행 X 열 → Sink로 해준다.

1. 처음 Flow를 흘리면
    - prev[] ⇒  -1 0 0 0 0 1 1 1 1 5 가 된다. :

        행은 Source에서 들어왔고, 
        모든 열은 행 1에서 들어왔고, 
        Sink는 열 5에서 들어왔다.

    - Flow를 역방향으로 거슬러가면

        열 5 → Sink 9로 1만큼,
        Sink 9 → 열 5로 -1만큼,
        행 1 → 열 5로 1만큼,
        열 5 → 행 1로 -1만큼,
        Source 0 → 행 1로 1만큼,
        행 1 → Source 0로 -1만큼,

2. 두 번째 Flow를 흘리면
    - prev[] ⇒ 1 0 0 0 0 2 1 1 1 6
    - Flow를 역방향으로 거슬러가면

        열 6 → Sink 9로 1만큼,
        Sink 9 → 열 6로 -1만큼,
        행 1 → 열 6로 1만큼,
        열 6 → 행 1로 -1만큼,
        Source 0 → 행 1로 2만큼,
        행 1 → Source 0로 -2만큼,

    ⇒ 행1 은 2의 Capacity를 다 찬 포화상태가 됬을 것이다. 다음은 아마 행1을 무시하고 다른 경로로 갈 것.

3. 세번 째 Flow를 흘리면
    - prev[] ⇒ 1 6 0 0 0 2 2 2 2 5
    - Flow를 역방향으로 거슬러가면

        열 5 → Sink 9로 2만큼,
        Sink 9 → 열 5로 -2만큼,
        행 2 → 열 5로 1만큼,
        열 5 → 행 2로 -1만큼,
        Source 0 → 행 2로 1만큼,
        행 2 → Source 0로 -1만큼,

    ⇒ 현재 까지 행1과 행2 2번, 1번씩 거치고, 열5를 2번, 열6을 1번 거쳐 Sink에 3개가 도달했다.
    행1, 열5는 모든 Capacity를 써서 다른 행, 열을 경로로 갈 것이다.

4. 네번째 Flow를 흘리면
    - prev[] ⇒ 2 5 0 0 0 3 2 2 2 6
    - Flow를 역방향으로 거슬러가면

        열 6 → Sink 9로 2만큼,
        Sink 9 → 열 6로 -2만큼,
        행 2 → 열 6로 1만큼,
        열 6 → 행 2로 -1만큼,
        Source 0 → 행 2로 2만큼,
        행 2 → Source 0로 -2만큼,

    ⇒ 이제 행1, 열5를 무시하고 행2, 열6을 사용하여 Sink까지 간다.

5. 생략... ... 
6. 이 문제에서 3번 더 흘러가 7번을 흘려주게 되면

    prev[] ⇒ -1 -1 -1 -1 -1 -1 -1 -1

    가 나오고, 

    1100
    1110
    0010
    0001

    로 Flow가 7만큼 흘러 1의 개수가 7인 행렬이 나오게 된다.

# Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int N, S, T;
vector <int> CapacityCol;
vector <int> CapacityRow;
vector <vector<int> > graphs;
vector <vector<int>> capacity;
vector <vector<int>> flow;
vector <vector<int>> result;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    CapacityCol.resize(N+1); CapacityRow.resize(N+1);
    graphs.resize(N+N+2); capacity.resize(N+N+2, vector<int>(N+N+2, 0)); flow.resize(N+N+2, vector<int>(N+N+2, 0));
    result.resize(N+1, vector<int>(N+1, 0));
    S = 0; T = N+N+1;
    for(int i=1; i<=N; i++){
        cin >> CapacityRow[i];
        graphs[S].push_back(i);
        graphs[i].push_back(S);
        capacity[S][i] = CapacityRow[i];
    }
    for(int i=N+1; i<=N+N; i++){
        cin >> CapacityCol[i-N];
        graphs[i].push_back(T);
        graphs[T].push_back(i);
        capacity[i][T] = CapacityCol[i-N];
    }
    for(int i=1; i<=N; i++){
        for(int j=N+1; j<=N+N; j++){
            graphs[i].push_back(j);
            graphs[j].push_back(i);
            capacity[i][j] = 1;
        }
    }
}

void NetworkFlow(){
    while(1){
        vector <int> prev(N+N+2, -1);

        queue <int> q;
        q.push(S);

        while(!q.empty()){
            int curr = q.front(); q.pop();

            for(auto &next : graphs[curr]){
                if(prev[next] != -1) continue;

                if(capacity[curr][next] > flow[curr][next]){
                    q.push(next);
                    prev[next] = curr;
                    if(next == T) break;
                }
            }
        }
        for(int i=0; i<N+N+2; i++){
            cout << prev[i]<<' ';
        }cout <<'\n';
        if(prev[T] == -1) break;

        int minFlow = 2147483647;
        for(int i=T; i != S; i=prev[i]){
            minFlow = min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i] );
        }
        cout<<"FLOW\n";
        for(int i=T; i != S; i=prev[i]){
            flow[prev[i]][i] += minFlow;
            flow[i][prev[i]] -= minFlow;

            cout << prev[i] << " => "<<i<<" "<<flow[prev[i]][i]<<'\n';
            cout << i<<" => "<<prev[i]<<" "<<flow[i][prev[i]]<<'\n';
        }cout <<'\n';

    }
    for(int i=1; i<=N; i++){
        for(int j=N+1; j<=N+N; j++){
            if(flow[i][j]){
                result[i][j-N] = 1;
            }
        }
    }
}
void print(){

    for(int i=1; i<=N; i++){
        int rowSum = 0;
        for(int j=1; j<=N; j++){
            rowSum += result[i][j];
        }
        if(rowSum != CapacityRow[i]){
            cout << "-1";
            return;
        }
    }
    for(int i=1; i<=N; i++){
        int colSum = 0;
        for(int j=1; j<=N; j++){
            colSum += result[j][i];
        }

        if(colSum != CapacityCol[i]){
            cout << "-1";
            return;
        }
    }
    cout << "1"<<'\n';
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout << result[i][j];
        }cout << '\n';
    }
}
int main(){
    input();
    for(int i=0; i<N+N+2; i++){
        cout << "i : "<<i<<" \n";
        for(auto &graph : graphs[i]){
            cout << graph<<' ';
        }cout << '\n';
    }
    NetworkFlow();
    print();
}
```

![1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled%202.png](1960_%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%86%E1%85%A1%E1%86%AB%E1%84%83%E1%85%B3%E1%86%AF%E1%84%80%E1%85%B5%20762c7a05a0484594a2baf098e2331f9f/Untitled%202.png)