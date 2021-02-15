#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector <vector<int>> trees;
vector <int> times;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; trees.resize(N); times.resize(N);
    int temp;
    for(int i=0; i<N; i++){
        cin >> temp;
        if(temp == -1) continue;
        times[temp] += 1;
        trees[temp].push_back(i); // Child Node Add
    }
}
void treePrint(){
    for(int i=0 ;i<times.size(); i++){
        cout << i<< " : "<<times[i]<<'\n';
    }cout <<'\n';
}
int propagation(int curr){
    if(times[curr] == 0){
        // leaf Node
        return 0;
    }
    vector<int> childTimes;
    for(auto &child : trees[curr]){
        int tempTime = propagation(child);
        childTimes.push_back(tempTime);
    }

    sort(childTimes.begin(), childTimes.end());

    int callTime = childTimes.size();
    for(auto &childTime : childTimes){
        times[curr] = max(times[curr], childTime+callTime--);
    }

    return times[curr];
}

int main(){
    input();
    propagation(0);
    //treePrint();
    cout << times[0];
}