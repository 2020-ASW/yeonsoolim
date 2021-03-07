# 11437_LCA

#최소 공통 조상  [최소 공통 조상 (Lowest Common Ancestor)](https://www.notion.so/Lowest-Common-Ancestor-78fa02e169ee46fcb93a06ebba79c6aa) #DP

# Problem

## 문제

N(2 ≤ N ≤ 50,000)개의 정점으로 이루어진 트리가 주어진다. 트리의 각 정점은 1번부터 N번까지 번호가 매겨져 있으며, 루트는 1번이다.

두 노드의 쌍 M(1 ≤ M ≤ 10,000)개가 주어졌을 때, 두 노드의 가장 가까운 공통 조상이 몇 번인지 출력한다.

## 입력

첫째 줄에 노드의 개수 N이 주어지고, 다음 N-1개 줄에는 트리 상에서 연결된 두 정점이 주어진다. 그 다음 줄에는 가장 가까운 공통 조상을 알고싶은 쌍의 개수 M이 주어지고, 다음 M개 줄에는 정점 쌍이 주어진다.

## 출력

M개의 줄에 차례대로 입력받은 두 정점의 가장 가까운 공통 조상을 출력한다.

# Solve 1

- 하나 씩 공통 조상 찾기

![11437_LCA%20e3a3750778044c5183893fee1065c435/Untitled.png](11437_LCA%20e3a3750778044c5183893fee1065c435/Untitled.png)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int N, M, a, b;
vector<vector<int>> trees;
vector <int> depth;
vector <int> parent;
vector <bool> visit;
void initDepth(){
    depth.resize(N+1); depth[1] = 1;
    parent.resize(N+1);
    visit.resize(N+1);
    queue <int> q;
    q.push(1);
    parent[1] = 0;
    visit[1] = true;
    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(auto &next : trees[curr]){
            if(visit[next]) continue;
            //cout << "curr : "<<curr<<'\t'<<next<<'\n';
            depth[next] = depth[curr]+1;
            visit[next] = true;
            parent[next] = curr;
            q.push(next);
        }
    }
}
int LCA(int left, int right){
    int answer = 0;
    //cout << "left : "<<left <<' '<<depth[left]<<' '<<"right : "<<right<< ' '<<depth[right]<<'\n';
    if(depth[left] < depth[right]) swap(left, right);

    while(depth[left] > depth[right]){
        //cout << "left : "<<left <<"= => "<<parent[left]<<'\n';
        left = parent[left];
    }
    //cout << "left : "<<left <<' '<<depth[left]<<' '<<"right : "<<right<< ' '<<depth[right]<<'\n';
    if(left == right) return left;

    if(depth[left] == depth[right]){
        int nextL = left, nextR = right;
        for(int i=1; ; i++){
            nextL = parent[nextL];
            nextR = parent[nextR];
            if(nextL == nextR){
                answer = nextL;
                break;
            }
        }
    }
    return answer;
}

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    trees.resize(N+1);
    for(int i=0; i<N-1; i++){
        cin >> a >> b;
        trees[a].push_back(b);
        trees[b].push_back(a);
    }

    initDepth();

    cin >> M;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
int main(){
    input();
}
```

# Solve 2

- Log 씩 공통 조상 찾기

![11437_LCA%20e3a3750778044c5183893fee1065c435/Untitled%201.png](11437_LCA%20e3a3750778044c5183893fee1065c435/Untitled%201.png)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#define MAXEXP 16

using namespace std;
int N, M, a, b;
vector<vector<int>> trees;
vector <int> depth;
vector <vector<int>> ancestors;

void setAncestor(int curr, int parent){
    depth[curr] = depth[parent]+1;
    ancestors[curr][0] = parent;
    for(int i=1; i<= MAXEXP; i++){
        int _next = ancestors[curr][i-1];
        ancestors[curr][i] = ancestors[_next][i-1];
    }

    for(auto &next : trees[curr]){
        if(next == parent) continue;
        setAncestor(next, curr);
    }
}

void initAncestor(){
    depth.resize(N+1);
    ancestors.resize(N+1); for(auto &ancestor : ancestors) ancestor.resize(MAXEXP+1);

    setAncestor(1, 0);
}
int LCA(int left, int right){
    int answer = 0;
    if(depth[left] < depth[right]) swap(left, right);

    while(depth[left] != depth[right]){

        left = ancestors[left][0];
        if(depth[left] < depth[right]) right = ancestors[right][1];
    }
    //cout << "left : "<<left <<' '<<depth[left]<<' '<<"right : "<<right<< ' '<<depth[right]<<'\n';
    if(left == right) return left;
    //cout << "left : "<<left <<' '<<"right : "<<right<< ' '<<'\n';

    int nextL, nextR;
    for(int i=MAXEXP; i>=0; i--){

        if(ancestors[left][i] != ancestors[right][i]){

            left = ancestors[left][i];
            right = ancestors[right][i];
        }
        //cout << "left : "<<left <<' '<<"right : "<<right<< ' '<<'\n';

        answer = ancestors[left][i];
    }

    return answer;
}

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    trees.resize(N+1);
    for(int i=0; i<N-1; i++){
        cin >> a >> b;
        trees[a].push_back(b);
        trees[b].push_back(a);
    }

    initAncestor();

    cin >> M;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
int main(){ // 31
    input();
}
```