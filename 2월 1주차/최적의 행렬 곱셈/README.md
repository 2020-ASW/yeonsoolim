# Programmers 12942 최적의 행렬 곱셈

---

# Pre

[Programmers 1843 사칙연산](https://www.notion.so/Programmers-1843-ee43dbe76f9a4b7fb84e00cf1adc4c2b)

과 아~~~주 유사하다. 그냥 똑같다.

# Warning

단, 사칙연산은 현재 보는 left, k, right에 해당하는 것들을 그대로 연산해주면 되지만,

이 문제는 행렬에 대한 누적 값 따로, 행렬에 대한 계수(정수) 따로 보면서 연산을 해주어야 한다.

# Solve

1. **2개의 행렬을 곱 하려면 3개의 수가 필요하다.**

    ```cpp
    void preExtraction(vector<vector<int>> &matrix){
        for(int i=0; i<matrix.size(); i+=2){
            pre.push_back(matrix[i][0]);
            pre.push_back(matrix[i][1]);
        }
        if(matrix.size() %2 == 0){
            pre.push_back(matrix[matrix.size()-1][1]);
        }
    }
    ```

2. **minimum(최소)값을 구할 것이므로 초기화를 INTMAX로 해준다.**

    ```cpp
    dp.resize(matrix_sizes.size()); for(auto &d : dp) d.resize(matrix_sizes.size());
    for(int i=0; i<matrix_sizes.size(); i++){
        for(int j=0; j<matrix_sizes.size(); j++){
            dp[i][j] = 2147483647;
        }
    }
    for(int i=0; i<dp.size(); i++) dp[i][i] = 0;
    ```

3. **DP를 돌면서 dp[left][right] 에 해당하는 값은 : left ~ right까지 행렬의 곱이고,
행렬에 누적된 dp 2개 +  행렬 곱셈에 대한 결과 ( pre[left] * pre[k+1] * pre[righ+1] )이 사용된다.**

    ```cpp
    for(int pos = 1; pos<pre.size(); pos++){
        for(int left=0; left<pre.size()-pos-1; left++){
            int right = left + pos;
            for(int k=left; k<right; k++){
                dp[left][right] = min(dp[left][right], dp[left][k] + dp[k+1][right]+(ll)pre[left]*pre[k+1]*pre[right+1]);
            }
        }
    }
    ```

    **`pos` : 몇 개의 행렬을 볼 것인지에 대한 수**

    **`left` : 가장 왼쪽의 행렬**

    **`right`  : 가장 오른쪽의 행렬  : left에서 pos만큼 떨어진 행렬**

    **`k` :  left와 right 사이에서 구간을 나눠줄 수**

    **example)**

    ![Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled.png](Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled.png)

    ![Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled%201.png](Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled%201.png)

4. 이렇게 쭉 DP를 진행하면 ? 

    dp [left][right] 중, left == 0  right == 행렬의 갯수 -1 

    ⇒ 0~N-1 

# Code

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
vector <int> pre;    
vector <vector <ll> > dp;

ll multiply(vector<int> a, vector <int> b){
    return (ll)a[0]*b[1]*a[1];
}
void preExtraction(vector<vector<int>> &matrix){
    for(int i=0; i<matrix.size(); i+=2){
        pre.push_back(matrix[i][0]);
        pre.push_back(matrix[i][1]);
    }
    if(matrix.size() %2 == 0){
        pre.push_back(matrix[matrix.size()-1][1]);
    }
}
int solution(vector<vector<int>> matrix_sizes) {
    int answer = 0;
    preExtraction(matrix_sizes);
    
    dp.resize(pre.size()); for(auto &d : dp) d.resize(pre.size());
    for(int i=0; i<pre.size(); i++){
        for(int j=0; j<pre.size(); j++){
            dp[i][j] = 2147483647;
        }
    }
    //for(int i=0; i<pre.size(); i++) cout <<pre[i]<<' ';
    //cout<<'\n';
    for(int i=0; i<dp.size(); i++) dp[i][i] = 0;
    for(int pos = 1; pos<pre.size(); pos++){
        for(int left=0; left<pre.size()-pos-1; left++){
            int right = left + pos;
            for(int k=left; k<right; k++){
                // cout << left<<' '<<k<<' '<<right<<'\n';
                dp[left][right] = min(dp[left][right], dp[left][k] + dp[k+1][right]+(ll)pre[left]*pre[k+1]*pre[right+1]);
                //cout << dp[left][k]<<' '<<dp[k+1][right]<<' '<<' '<<pre[left]<<' '<<pre[k+1]<<' '<<pre[right+1]<<'\n';
                //cout << "left : "<<left <<" "<<"K : "<<k<<" right : "<<right<<' '<<"total : "<<dp[left][right]<<"\n\n";
            }
            
        }
    }
    
    return dp[0][matrix_sizes.size()-1];
}
```

![Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled%202.png](Programmers%2012942%20%E1%84%8E%E1%85%AC%E1%84%8C%E1%85%A5%E1%86%A8%E1%84%8B%E1%85%B4%20%E1%84%92%E1%85%A2%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF%20%E1%84%80%E1%85%A9%E1%86%B8%E1%84%89%E1%85%A6%E1%86%B7%20652520ae95114368baba63ed2039e3f3/Untitled%202.png)