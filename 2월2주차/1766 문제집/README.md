# 1766 문제집

# sort # Topology Sort  #중간에 끼워넣기

# 문제

- 1 ~ N개의 문제가 있다.
- 1~N으로 갈 수록 난이도는 상승한다.
- 우선순위가 정해진 문제가 있다면 그 문제를 먼저 풀어야 한다.
- **난이도가 가장 쉬운 문제를 우선으로 풀어야 한다.
(이게 일반적인 위상정렬과 다른 부분)**

# Error

사소하지만, 큰 실수, 자식의 Indegree를 빼고 queue에 넣어줬어야 했다.

# Solve

1. **위상정렬을 준비한다.**

    **→ Node별로 앞서야 하는 Node가 있는지 확인해준다.
    → 자식이 있는지 확인해준다.  :  이 문제를 해결하면 연달아 해결할 수 있는 난이도가 쉬운 문제**

    ```cpp
    for(int i=0; i<M; i++){
        int a, b;
        cin >> a >> b;
        indegree[b]++;
        childs[a].insert(b);
    }
    for(int i=1; i<=N; i++){
        if(indegree[i] == 0) pq.push({indegree[i], i});
    }
    ```

2. **위상정렬 Priority Queue에서 우선순위는 Indegree가 0인것 → Index가 작은 것 (난이도가 쉽다)**

    ```cpp
    struct cmp{
        bool operator()(const pair<int,int> &a, const pair<int,int> &b){
            if(a.first == b.first) return a.second > b.second;
            return a.first > b.first;
        }
    };

    priority_queue <pair<int,int>, vector <pair<int,int> > , cmp> pq;
    ```

3. **Indegree가 0이라면 앞서 나올 수 있는데,
일반적인 위상정렬이라면 현재 Indegree가 0인 것 중에서 순서대로 나올 것.
하지만, 자식들을 먼저 고려해준다.**

    ```cpp
    void search(int parent){
        answer.push_back(parent);
        for(auto &child : childs[parent]){
            indegree[child]--;
            if(indegree[child] == 0){
                pq.push({indegree[child], child});
            }
        }
    }

    void tpSort(){
        while(!pq.empty()){
            pair<int,int> now = pq.top(); pq.pop();
            if(now.first == 0){
                **search(now.second);**
            }else{
                pq.push({now.first-1,now.second });
            }
        }
    }
    ```

# Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;
struct cmp{
    bool operator()(const pair<int,int> &a, const pair<int,int> &b){
        if(a.first == b.first) return a.second > b.second;
        return a.first > b.first;
    }
};
int N, M;  //문제의 수, 정보의 개수
vector <int> indegree;
vector <int> answer;
vector <set<int> > childs;
priority_queue <pair<int,int>, vector <pair<int,int> > , cmp> pq;

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    indegree.resize(N+1);
    childs.resize(N+1);
    for(int i=0; i<M; i++){
        int a, b;
        cin >> a >> b;
        indegree[b]++;
        childs[a].insert(b);
    }
    for(int i=1; i<=N; i++){
        if(indegree[i] == 0) pq.push({indegree[i], i});
    }
}

void search(int parent){
    answer.push_back(parent);
    for(auto &child : childs[parent]){
        indegree[child]--;
        if(indegree[child] == 0){
            pq.push({indegree[child], child});
        }
    }
}

void tpSort(){
    while(!pq.empty()){
        pair<int,int> now = pq.top(); pq.pop();
        if(now.first == 0){
            search(now.second);
        }else{
            pq.push({now.first-1,now.second });
        }
    }
}
int main(){
    input();
    if(N==1){
        cout << "1";
        exit(0);
    }
    tpSort();
    for(int i=0; i<answer.size(); i++){
        cout << answer[i]<<' ';
    }
}
```

![https://github.com/2020-ASW/yeonsoolim/blob/master/2%EC%9B%942%EC%A3%BC%EC%B0%A8/1766%20%EB%AC%B8%EC%A0%9C%EC%A7%91/1766%20%EB%AC%B8%EC%A0%9C%EC%A7%91%20f9615653571d4e3d842e9b947aacb9f3/Untitled.png?raw=true](1766%20%E1%84%86%E1%85%AE%E1%86%AB%E1%84%8C%E1%85%A6%E1%84%8C%E1%85%B5%E1%86%B8%20f9615653571d4e3d842e9b947aacb9f3/Untitled.png)
