#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int R, L, answer;
ll B;

vector <int> riceX;
vector <ll> prefixSum;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> R >> L >> B; riceX.resize(R+1); prefixSum.resize(R+1);
    for(int i=1; i<=R; i++) cin >> riceX[i];

}
void initPrefixSum(){
    //prefixSum can  좌표, 좌표별 누적합, 거리  구할 수 있음.
    for(int i=1; i<=R; i++) prefixSum[i] = prefixSum[i-1] + (ll)riceX[i];
}

bool checkBudget(int sectionL, int sectionR){

    int sectionM = (sectionR - sectionL)/2 + sectionL;

    ll leftAccumulate = prefixSum[sectionM - 1] - prefixSum[sectionL - 1];
    int leftRiceCnt = sectionM - sectionL;
    ll leftCoordSum = riceX[sectionM]*(ll)leftRiceCnt - leftAccumulate;

    ll rightAccumulate = prefixSum[sectionR] - prefixSum[sectionM];
    int rightRiceCnt = sectionR - sectionM;
    ll rightCoordSum = rightAccumulate - riceX[sectionM] * (ll)rightRiceCnt;

    if(leftCoordSum + rightCoordSum <= B) return true;
    return false;
}

void searchStorage(){
    int sectionL, sectionR;
    // ToDo :  구간을 얼마나 넓게 볼 것인가.   Parametric : 구간에 대한 예산의 적절성 여부.

    for(sectionL = sectionR = 1; sectionR <=R;){
        if(checkBudget(sectionL, sectionR)){
            answer = max(answer, sectionR - sectionL + 1);
            sectionR++;
        }else{
            sectionL++;
            if(sectionL > sectionR) sectionR++;
        }
    }
}
int main(){
    input();
    initPrefixSum();
    searchStorage();
    cout << answer;
}