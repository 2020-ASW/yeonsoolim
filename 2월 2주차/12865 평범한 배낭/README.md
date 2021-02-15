# 12865 평범한 배낭

---

[배낭 알고리즘 (knabsack)](https://www.notion.so/knabsack-276a1369c8564ec19260cc1f5fe3161a)

# Problem

![12865%20%E1%84%91%E1%85%A7%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%87%E1%85%A2%E1%84%82%E1%85%A1%E1%86%BC%2026b3526b2a1947fcbe3f56b3de7ff2bc/Untitled.png](12865%20%E1%84%91%E1%85%A7%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%87%E1%85%A2%E1%84%82%E1%85%A1%E1%86%BC%2026b3526b2a1947fcbe3f56b3de7ff2bc/Untitled.png)

# Pre

- Greedy로 풀 수 있을까?

    → Weight or Value 로 정렬 후, 최적의 값을 선택 한다 해도 최상의 값을 보장할 수 없을 것 같다.

# Solve

- 배낭 알고리즘

    DP 이용

![12865%20%E1%84%91%E1%85%A7%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%87%E1%85%A2%E1%84%82%E1%85%A1%E1%86%BC%2026b3526b2a1947fcbe3f56b3de7ff2bc/Untitled%201.png](12865%20%E1%84%91%E1%85%A7%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%87%E1%85%A2%E1%84%82%E1%85%A1%E1%86%BC%2026b3526b2a1947fcbe3f56b3de7ff2bc/Untitled%201.png)

1. **DP 만들기**

    ```cpp
    void makeDP(){
        for(int j=0; j<=K; j++){
            if(items[0].weight > j) dp[0][j] = 0;
            else dp[0][j] = items[0].value;
        }
        for(int i=1; i<N; i++){
            for(int j=0; j<=K; j++){
                // i : item의 Index
                // j : 현재 가방 무게
                if(items[i].weight > j) dp[i][j] = dp[i-1][j];
                // 넣고도 남는 자리가 있을 수 있다.   j-items[i].weight => 남는 무게 중 가장 큰
                else dp[i][j] = max(dp[i-1][j], items[i].value +  dp[i-1][j-items[i].weight]);
            }
        }
    }
    ```

2. max값 가져오기

    ```cpp
    ~~void getMax(){
        int answer = 0;
        for(int i=0; i<N; i++) answer = max(answer, dp[i][K]);
        cout << answer;
    }~~

    void getMax(){
        cout << dp[N-1][K];
    }
    ```

# Error

물품 번호 : row에 관해서 그 물품은 꼭 넣어야 할줄 알았는데,

직전이 아닌 그 전의 내용들을 가져올려면 계속 max를 이용해서 유지해주어야 한다.

⇒ DP의 목적

# Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;
struct weightValue{
    int weight;
    int value;
};
vector <weightValue> items;
vector <vector <int> > dp;
int N, K, w, v;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    dp.resize(N); for(auto &d: dp) d.resize(K+1);
    for(int i=0; i<N; i++){
        cin >> w >> v;
        items.push_back({w,v});
    }
}
void makeDP(){
    for(int j=0; j<=K; j++){
        if(items[0].weight > j) dp[0][j] = 0;
        else dp[0][j] = items[0].value;
    }
    for(int i=1; i<N; i++){
        for(int j=0; j<=K; j++){
            // i : item의 Index
            // j : 현재 가방 무게
            if(items[i].weight > j) dp[i][j] = dp[i-1][j];
            // 넣고도 남는 자리가 있을 수 있다.   j-items[i].weight => 남는 무게 중 가장 큰
            else dp[i][j] = max(dp[i-1][j], items[i].value +  dp[i-1][j-items[i].weight]);
        }
    }
}
void getMax(){
//    int answer = 0;
//    for(int i=0; i<N; i++) answer = max(answer, dp[i][K]);
//    cout << answer;
    cout << dp[N-1][K];
}
int main(){
    input();
    makeDP();
    getMax();
}
```