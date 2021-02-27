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