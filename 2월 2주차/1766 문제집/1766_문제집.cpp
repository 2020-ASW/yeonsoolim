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