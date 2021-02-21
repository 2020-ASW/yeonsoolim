#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;
int N, answer;
vector <vector <int> > graphs;
vector <int> pointing;
vector <int> pointed;
vector <int> visit;
unordered_set <int> mapia;
unordered_set <int> human;
void input() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    graphs.resize(N + 1);
    visit.resize(N + 1);
    pointing.resize(N + 1);
    pointed.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> pointing[i];
        graphs[i].push_back(pointing[i]);
        graphs[pointing[i]].push_back(i);
        pointed[pointing[i]]++;
    }
}

void searchDFS(int node, bool isMapia){
    if(visit[node]) return;

    visit[node] = 1;
    if(isMapia) answer++;
    int next = pointing[node];
    //if(visit[next]) return;
    //visit[next] = 1;

    //®cout << "Dfs : "<<next<<' '<<pointed[next]<<'\n';
    pointed[next]--;
    if(pointed[next] == 0 || isMapia){
        searchDFS(next, !isMapia);
    }
//    if(pointed[next] == 0 || isMapia){
//        human.insert(next);
//        searchDFS(next, false);
//    }else{
//        if(mapia.find(pointing[next]) != mapia.end()){
//            human.insert(next);
//            searchDFS(next, false);
//        }else{
//            mapia.insert(next);
//            searchDFS(next, true);
//        }
//    }
}

void searchMapia(){
    for(int i=1; i<=N; i++){
        //cout << "search : "<<i<<' '<<pointed[i]<<'\n';
        if(pointed[i] == 0){
            searchDFS(i, true);
        }
    }
    for(int i=1 ;i<=N; i++){
        searchDFS(i, false);
    }
}


int main() {
	input();
    searchMapia();
//    cout << "MAPIA : ";
//    for(auto &ma : mapia){
//        cout <<ma<<' ';
//    }cout << '\n';
//    cout << "HUMNA : ";
//    for(auto &hu : human){
//        cout << hu<<' ';
//    }cout << '\n';

	cout << answer;

}