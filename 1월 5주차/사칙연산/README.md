# Programmers 1843 사칙연산

---

# Pre

괄호가 중복이 되기 때문에 

처럼 모든 식을 구할 수는 없다.

# Solve

```cpp
for(int pos = 1; pos <arr.size()/2+1; pos++){  //간격
    for(int left = 0; left <arr.size()/2+1-pos; left++){
        int right = left + pos;
        for(int k = left; k<right; k++){
            if(arr[k*2+1] == "+"){
                // + 일때  최대 : 최대 + 최대  최소 : 최소 + 최소
                dp[left][right][1] = max(dp[left][k][1] + dp[k+1][right][1] ,dp[left][right][1]);
                dp[left][right][0] = min(dp[left][k][0] + dp[k+1][right][0], dp[left][right][0]);
        
            }else{
                // - 일때  최대 : 최대 - 최소  최소 : 최소 - 최대
                dp[left][right][1] = max(dp[left][k][1] - dp[k+1][right][0] , dp[left][right][1]);
                dp[left][right][0] = min(dp[left][k][0] - dp[k+1][right][1] , dp[left][right][0]);
   
            }        
        }
     }
}
```

![Programmers%201843%20%E1%84%89%E1%85%A1%E1%84%8E%E1%85%B5%E1%86%A8%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%89%E1%85%A1%E1%86%AB%2015802426973740ceaa35cdda7e488e0c/Untitled.png](Programmers%201843%20%E1%84%89%E1%85%A1%E1%84%8E%E1%85%B5%E1%86%A8%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%89%E1%85%A1%E1%86%AB%2015802426973740ceaa35cdda7e488e0c/Untitled.png)

# Warning

- 최대, 최소 값을 구할 때는 초기화 상태가 중요.

# Code

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[101][101][2];
void init(vector<string> &arr){
    for(int i=0; i<101; i++){
        for(int j=0; j<101; j++){
            dp[i][j][1] = -100000;
            dp[i][j][0] = 100000;
        }
    }
    for(int i=0; i<arr.size()/2+1; i++) dp[i][i][0] = dp[i][i][1] = stoi(arr[i*2]);
}
void DP(vector<string> &arr){
    for(int pos = 1; pos <arr.size()/2+1; pos++){  //간격
        for(int left = 0; left <arr.size()/2+1-pos; left++){
            int right = left + pos;
            for(int k = left; k<right; k++){
                if(arr[k*2+1] == "+"){
                    // + 일때  최대 : 최대 + 최대  최소 : 최소 + 최소
                    dp[left][right][1] = max(dp[left][k][1] + dp[k+1][right][1] ,dp[left][right][1]);
                    dp[left][right][0] = min(dp[left][k][0] + dp[k+1][right][0], dp[left][right][0]);
            
                }else{
                    // - 일때  최대 : 최대 - 최소  최소 : 최소 - 최대
                    dp[left][right][1] = max(dp[left][k][1] - dp[k+1][right][0] , dp[left][right][1]);
                    dp[left][right][0] = min(dp[left][k][0] - dp[k+1][right][1] , dp[left][right][0]);
       
                }        
            }
         }
    }
}
int solution(vector<string> arr)
{

    init(arr);
    DP(arr);
    
    return dp[0][arr.size()/2][1];
}
```

![Programmers%201843%20%E1%84%89%E1%85%A1%E1%84%8E%E1%85%B5%E1%86%A8%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%89%E1%85%A1%E1%86%AB%2015802426973740ceaa35cdda7e488e0c/PNG__6.png](Programmers%201843%20%E1%84%89%E1%85%A1%E1%84%8E%E1%85%B5%E1%86%A8%E1%84%8B%E1%85%A7%E1%86%AB%E1%84%89%E1%85%A1%E1%86%AB%2015802426973740ceaa35cdda7e488e0c/PNG__6.png)