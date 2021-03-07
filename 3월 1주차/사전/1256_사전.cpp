#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#define ll long long
#define LIMIT 1000000000

using namespace std;
int N, M, K;
vector <vector<int> > nCr;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
}
void init_nCr(){
    nCr.resize(201); for(auto &a : nCr) a.resize(201);
    nCr[0][0] = nCr[1][0] = nCr[1][1] = 1;
    for(int i=1; i<=N+M; i++){
        nCr[i][0] = 1;
        for(int j=1; j<=i; j++){
            //nCr[i][j] = min(LIMIT, nCr[i-1][j] + nCr[i-1][j-1]);
            nCr[i][j] = nCr[i - 1][j] + nCr[i - 1][j - 1];
            if (nCr[i][j] > LIMIT) nCr[i][j] = LIMIT;
        }
    }
}

string check(){
    string answer;
    while (M>0 && N>0) {
        /*cout << "N : " << N << ' ' << "M : " << M << '\n';
        cout << nCr[N + M][M] << ' ' << nCr[N + M - 1][M - 1] << "  :  " << K << '\n';
        cout << nCr[N + M][M] - nCr[N + M - 1][M - 1] << '\n';*/
        //if (nCr[N + M][M] - nCr[N + M - 1][M - 1] >= K) {
        if(nCr[N+M-1][M] >= K){
            answer += "a";
            N--;
        }
        else {
            answer += "z";
            //K -= nCr[N + M][M] - nCr[N + M - 1][M - 1];
            K -= nCr[N + M - 1][M];
            M--;
        }
    }
    for (int i = 0; i < M; i++) answer += "z";
    for (int i = 0; i < N; i++) answer += "a";
    return answer;
}
int main(){
    input();
    init_nCr();
    if (nCr[N + M][M] < K) cout << "-1" << '\n';
    else cout << check() <<'\n';
}
