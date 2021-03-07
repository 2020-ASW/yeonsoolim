//#include <iostream>
//#include <vector>
//#include <queue>
//#include <algorithm>
//
//using namespace std;
//int N, M, a, b;
//vector<vector<int>> trees;
//vector <int> depth;
//vector <int> parent;
//vector <bool> visit;
//void initDepth(){
//    depth.resize(N+1); depth[1] = 1;
//    parent.resize(N+1);
//    visit.resize(N+1);
//    queue <int> q;
//    q.push(1);
//    parent[1] = 0;
//    visit[1] = true;
//    while(!q.empty()){
//        int curr = q.front(); q.pop();
//        for(auto &next : trees[curr]){
//            if(visit[next]) continue;
//            //cout << "curr : "<<curr<<'\t'<<next<<'\n';
//            depth[next] = depth[curr]+1;
//            visit[next] = true;
//            parent[next] = curr;
//            q.push(next);
//        }
//    }
//}
//int LCA(int left, int right){
//    int answer = 0;
//    //cout << "left : "<<left <<' '<<depth[left]<<' '<<"right : "<<right<< ' '<<depth[right]<<'\n';
//    if(depth[left] < depth[right]) swap(left, right);
//
//    while(depth[left] > depth[right]){
//        //cout << "left : "<<left <<"= => "<<parent[left]<<'\n';
//        left = parent[left];
//    }
//    //cout << "left : "<<left <<' '<<depth[left]<<' '<<"right : "<<right<< ' '<<depth[right]<<'\n';
//    if(left == right) return left;
//
//    if(depth[left] == depth[right]){
//        int nextL = left, nextR = right;
//        for(int i=1; ; i++){
//            nextL = parent[nextL];
//            nextR = parent[nextR];
//            if(nextL == nextR){
//                answer = nextL;
//                break;
//            }
//        }
//    }
//    return answer;
//}
//
//void input(){
//    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    cin >> N;
//    trees.resize(N+1);
//    for(int i=0; i<N-1; i++){
//        cin >> a >> b;
//        trees[a].push_back(b);
//        trees[b].push_back(a);
//    }
//
//    initDepth();
//
//    cin >> M;
//    for(int i=0; i<M; i++){
//        cin >> a >> b;
//        cout << LCA(a, b) << '\n';
//    }
//}
//int main(){ // 31
//    input();
//}
//


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

