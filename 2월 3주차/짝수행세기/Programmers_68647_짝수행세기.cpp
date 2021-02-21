#include <string>
#include <vector>
#define ll long long
#define MOD 10000019


using namespace std;

void getOneCnt(vector<vector<int>> &a, vector <int> &oneCnt){
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<a[i].size(); j++){
            oneCnt[j] += a[i][j];
        }
    }
}

void get_nCr(vector<vector<int>> &a, vector<vector<ll>> &nCr){
    // A에서 B만큼 뽑는 경우 수  i:행 index   j:갯수
    // j==0 : 0개 뽑는건 무조건 1개
    nCr[0][0] = 1;

    for(int i=1; i<=a.size(); i++){
        for(int j=0; j<=a.size(); j++){
            if(j==0) nCr[i][0] = 1;
            else if(i==j) nCr[i][j] = 1;
            else nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j])%MOD;
        }
    }
}

void getDP(vector<vector<int>> &a, vector<vector<ll>> &DP, vector <vector<ll> > &nCr, vector <int> &oneCnt){
    int Row = a.size();
    int Col = a[0].size();
    DP[1][Row-oneCnt[0]] = nCr[Row][Row - oneCnt[0]];

    for(int c=1; c<Col; c++){
        for(int now = 0; now <= Row; now++){
            if(DP[c][now] == 0) continue;
            for(int k=0; k<=oneCnt[c]; k++){
                if(now < k) continue;

                int next = (now - k) + (oneCnt[c] - k);
                if(next > Row) continue;

                ll result = (nCr[now][k] * nCr[Row-now][oneCnt[c] - k]) % MOD;
                DP[c+1][next] = (DP[c+1][next] + DP[c][now]*result)%MOD;
            }
        }
    }
}

int solution(vector<vector<int>> a) {
    vector <vector<ll> > DP(a[0].size()+1, vector<ll>(a.size()+1, 0));
    vector <vector<ll> > nCr(a.size()+1, vector<ll>(a.size()+1, 0));
    vector <int> oneCnt(a[0].size()+1, 0);

    getOneCnt(a, oneCnt);
    get_nCr(a, nCr);
    getDP(a, DP, nCr, oneCnt);
    return DP[(int)a[0].size()][(int)a.size()];
}