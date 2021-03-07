# 1256 사전

# Problem

## 문제

동호와 규완이는 212호에서 문자열에 대해 공부하고 있다. 김진영 조교는 동호와 규완이에게 특별 과제를 주었다. 특별 과제는 특별한 문자열로 이루어 진 사전을 만드는 것이다. 사전에 수록되어 있는 모든 문자열은 N개의 "a"와 M개의 "z"로 이루어져 있다. 그리고 다른 문자는 없다. 사전에는 알파벳 순서대로 수록되어 있다.

규완이는 사전을 완성했지만, 동호는 사전을 완성하지 못했다. 동호는 자신의 과제를 끝내기 위해서 규완이의 사전을 몰래 참조하기로 했다. 동호는 규완이가 자리를 비운 사이에 몰래 사전을 보려고 하기 때문에, 문자열 하나만 찾을 여유밖에 없다.

N과 M이 주어졌을 때, 규완이의 사전에서 K번째 문자열이 무엇인지 구하는 프로그램을 작성하시오.

## 입력

첫째 줄에 N, M, K가 순서대로 주어진다. N과 M은 100보다 작거나 같은 자연수이고, K는 1,000,000,000보다 작거나 같은 자연수이다.

## 출력

첫째 줄에 규완이의 사전에서 K번째 문자열을 출력한다. 만약 규완이의 사전에 수록되어 있는 문자열의 개수가 K보다 작으면 -1을 출력한다.

# Solve

1. nCr = n-1Cr + n-1Cr-1 이라는 파스칼의 법칙을 이용하여 전체 자릿 수(N+M)에서 Z가 오는 수 (M)을 구해놓는다.

    ```cpp
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
    ```

2. 로직
    1. N+M 중 M을 을 뽑는 경우의 수  N+M C M 은 'a' N개 'z' M개로 이루어져있다는 말이다.
        1. 만약 이 경우의 수 보다 K가 클 경우는 표현 할 수 있는 범위를 넘어갔으므로 -1을 출력해준다.
    2. 이 중, z를 1개 써버린다면? z가 해당 자리에 올 경우는 N+M-1 C M-1 이다. z가 1개 왔으므로, M이 줄어들고, M이 줄어들었으니 전체 자릿 수도 줄어든다.
    3. 이때, 총 경우의 수 (1) - z경우의 수(2)  사이에 있다면 해당 자리에는 'a'가 올 것이고, 그 위에 있다면 'z'가 와야 K  번째 수를 맞출 수 있다.
    4. 'a'가 오게 된다면 1~K번째는 유지되고, 그 이후 'z'로 시작하는 경우의 수만 사라지므로, N만 줄여준다.
    5. 'z'가 오게 된다면 1~K번째가 사라지고, 그 이후 'z'로 시작하는 경우이 수만 남게되므로, M을 줄여주고, K도 'a'의 수만큼 줄여주어야 한다. 

# Error

1. nCr에서 큰 수가 나오면 (10억 이상)으로 통일 해 놓았다.

    하지만, `if (nCr[N + M][M] - nCr[N + M - 1][M - 1] >= K)` 이 경우 LIMIT-LIMIT가 나올 수 있다. 0이 되어버림.

    ⇒ 파스칼의 법칙을 이용하여 `if(nCr[N+M-1][M] >= K)` 이 식으로 바꾸니 해결되었다.

# Example

![1256%20%E1%84%89%E1%85%A1%E1%84%8C%E1%85%A5%E1%86%AB%20340e93774dd149f3a4e0aa2592ecb169/Untitled.png](1256%20%E1%84%89%E1%85%A1%E1%84%8C%E1%85%A5%E1%86%AB%20340e93774dd149f3a4e0aa2592ecb169/Untitled.png)

# Code

```cpp
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
```