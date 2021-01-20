# Programmers 42861 (prim)섬 연결하기

MST

# Pre

1. *? 모든 섬 사이의 비용이 주어지지 않는다. 이 경우 건설이 불가능하다. ?* 
2. N : 섬의 개수 : 100
cost : 간선의 가중치 : 5000 이하 양수
3. 모든 Node를 지나가는 가장 짧은 비용의 Graph

    [Minimum Spanning Tree](https://www.notion.so/Minimum-Spanning-Tree-40232e1de14d4c209b68805c2c0ca68b)

# Solve

1. **Node를 1번씩만 방문한다.**
2. **방문 했을 때 Queue에 연결된 Edge를 넣어준다.**

    ```cpp
    for(auto &edge : edges[now]){
        if(visit.test(edge.first)) continue;
        pq.push({edge.first,edge.second});
    }
    ```

    Queue는 우선순위큐로 비용이 가장 낮은 것 순으로 꺼낸다.

    ```cpp
    struct cmp{
        bool operator()(const pair<int,int> &a, const pair<int,int> &b){
            return a.second > b.second;
        }
    };

    priority_queue <pair<int,int>, vector<pair<int,int> >, cmp> pq;
    ```

3. **pq에는 방문했던 Node들에 연결되 있는 Edge들만 있다.**
4. **Edge 의 끝 → 다음 방문할 Node를 안가본 곳만 간다.**

    ```cpp
    pair<int,int> next = pq.top(); pq.pop();
    if(visit.test(next.first)) continue;
    ```

5. **Node를 모두 돌았다면 스패닝트리가 되었다.**

    ```cpp
    while(visit.count() != n){
    		......
    }
    ```

# Code

```cpp
#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <queue>

using namespace std;
struct cmp{
    bool operator()(const pair<int,int> &a, const pair<int,int> &b){
        return a.second > b.second;
    }
};
vector <vector <pair<int,int> > > edges;
priority_queue <pair<int,int>, vector<pair<int,int> >, cmp> pq;
int totalNode, totalWeight;
bitset <100> visit;

void setEdges(vector<vector<int>> costs){
    edges.resize(totalNode);
    for(auto &cost : costs){
        edges[cost[0]].push_back({cost[1],cost[2]});
        edges[cost[1]].push_back({cost[0],cost[2]});
    }
}
void prim(){
    int now = 0; visit.set(0);
    while(visit.count() != totalNode){
        for(auto &edge : edges[now]){
            if(visit.test(edge.first)) continue;
            pq.push({edge.first,edge.second});
        }
        while(!pq.empty()){
            pair<int,int> next = pq.top(); pq.pop();
            if(visit.test(next.first)) continue;
            visit.set(next.first);
            totalWeight+=next.second;
            now = next.first;
            break;
        }
    }
}
int solution(int n, vector<vector<int>> costs) {
    totalNode = n;
    setEdges(costs);
    prim();
    return totalWeight;
}
```

![Programmers%2042861%20(prim)%E1%84%89%E1%85%A5%E1%86%B7%20%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%80%E1%85%A7%E1%86%AF%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%2025e6ba87c88a46058ec0c578ecf8ba34/Untitled.png](Programmers%2042861%20(prim)%E1%84%89%E1%85%A5%E1%86%B7%20%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%80%E1%85%A7%E1%86%AF%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%2025e6ba87c88a46058ec0c578ecf8ba34/Untitled.png)

![Programmers%2042861%20(prim)%E1%84%89%E1%85%A5%E1%86%B7%20%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%80%E1%85%A7%E1%86%AF%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%2025e6ba87c88a46058ec0c578ecf8ba34/programmers_42861__.png](Programmers%2042861%20(prim)%E1%84%89%E1%85%A5%E1%86%B7%20%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%80%E1%85%A7%E1%86%AF%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%2025e6ba87c88a46058ec0c578ecf8ba34/programmers_42861__.png)