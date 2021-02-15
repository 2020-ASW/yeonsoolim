#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long

using namespace std;
struct Tree{
    ll cost;
    ll mul;
};
ll answer=1;
int N, maxCoord;
vector <Tree> trees;
vector <int> X;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; X.resize(N+1); trees.resize( 1<< ((int)ceil(log2(200000))+1) );
    for(int i=1; i<=N; i++){
        cin >> X[i];
        maxCoord = max(maxCoord, X[i]);
    }
}

void update(int node, int start, int end, int idx){
    if(!(start <= idx && idx <= end)) return;
    trees[node].cost += 1;
    trees[node].mul += idx;

    if(start == end) return;

    int mid = (end-start)/2 + start;
    update(node*2, start, mid, idx);
    update(node*2+1, mid+1, end, idx);
}

ll costQuery(int node, int start, int end, int left, int right){
    if(right < start || end < left) return 0;

    if(left <= start && end <= right) return trees[node].cost;

    int mid = (end-start)/2 + start;
    return costQuery(node*2, start ,mid, left, right) + costQuery(node*2+1, mid+1, end, left, right);
}

ll mulQuery(int node, int start, int end, int left, int right){
    if(right < start || end < left) return 0;

    if(left <= start && end <= right) return trees[node].mul;

    int mid = (end-start)/2 + start;
    return mulQuery(node*2, start ,mid, left, right) + mulQuery(node*2+1, mid+1, end, left, right);
}

int main(){
    input();
    int temp = (1<<((int)ceil(log2(maxCoord)) + 1));
    for(int i=0; i<=temp; i++){
        cout << i<<" : "<<trees[i].cost<<'\n';
    }cout << '\n';
    for(int i=1; i<=N; i++){
        update(1, 0, maxCoord, X[i]);
        for(int i=0; i<=temp; i++){
            cout << i<<" : "<<trees[i].mul<<'\n';
        }cout << '\n';

        ll leftCost = costQuery(1, 0, maxCoord, 0, X[i]) * X[i] - mulQuery(1, 0, maxCoord, 0, X[i]);
        ll rightCost = mulQuery(1, 0, maxCoord, X[i]+1, maxCoord) - costQuery(1, 0, maxCoord, X[i]+1, maxCoord) * X[i];
        ll totalCost = (leftCost%1000000007 + rightCost%1000000007)%1000000007;
        if(i == 1) continue;
        answer = ((answer%1000000007) * (totalCost%1000000007))%1000000007;
    }
    cout << answer%1000000007;
}