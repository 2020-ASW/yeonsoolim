# LeetCode 239 Sliding Window Maximum

# 문제이해

- nums : 정수가 들어있는 배열
- k : 슬라이딩 윈도우의 크기
- 슬라이딩 윈도우가 1칸씩 전진하는 가운데, 가장 큰 정수를 모두 담은 배열을 리턴.

# Pre

**문제 이해를 잘못 했다.**

구간의 최대 정수가 아니라, 최대를 갖는 구간으로 해석.

- twopointer or segment tree
- DP로 풀기에는 k만큼 전의 값들도 봐야함.

# Solve

- 단순히, 슬라이딩 윈도우를 1칸씩 이동한다.
- 슬라이딩 윈도우 내에서 가장 큰 정수를 구별할 수 있어야 한다.
- 슬라이딩 윈도우가 지나기 전까지는 큰 정수가 남아있어야 한다.

### Deque

- 가장 왼쪽에 현재 슬라이딩 윈도우에서 가장 큰 정수의 **index**를 저장한다.

    **index : index가 아니라 정수를 저장하면, 가장 왼쪽의 정수를 빼내야할 타이밍(슬라이딩 윈도우가 끝날 때)을 체크할 수가 없다.**

    ![LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled.png](LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled.png)

- 새로운 정수를 체크할 때는 슬라이딩 윈도우 중 쓸데없는 수들은 지워 줘야 한다.

    : 지워주지 않으면 왼쪽에는 가장 큰 정수의 인덱스를 저장한다는 논리를 깨게 된다. (중간에 작은 값들이 들어가게 된다는 뜻)

    ```cpp
    void firstSetting(vector<int>& nums, int k){
        for(int i=0; i<k; i++){

    				// 쓰잘데기 없는 수는 무조건 지워줘야 한다.
            while(!dq.empty() && nums[dq.back()] < nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
        }
    }
    ```

- 슬라이딩 윈도우가 이동할 때 마다 왼쪽의 인덱스를 빼서 answer에 저장해주고,
왼쪽의 값이 빠질 타이밍이 되면, deque에서도 빼준다.

    ```cpp
    for(int i=k; i<nums.size(); i++){     // 슬라이딩 윈도우가 전진한다.
    		answer.push_back(nums[dq.front()]);
    		if(dq.front()+k == i){  //빠질 타이밍
    		    dq.pop_front();
    		}
    ```

# Code

```cpp
#include <algorithm>

class Solution {
public:
    
    deque <int> dq;
    vector <int> answer;

    void firstSetting(vector<int>& nums, int k){
        for(int i=0; i<k; i++){
            while(!dq.empty() && nums[dq.back()] < nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
        }
    }
    void print(){
        deque <int> ::iterator iter;
        for(iter=dq.begin(); iter!=dq.end(); ++iter){
            cout << *iter<<' ';
        }cout << '\n';
    }
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        firstSetting(nums, k);
        if(nums.size() == 1) return nums;
        
        for(int i=k; i<nums.size(); i++){
            answer.push_back(nums[dq.front()]);
            if(dq.front()+k == i){
                dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()] < nums[i]){   
                dq.pop_back();
            }
            dq.push_back(i);
        }
        answer.push_back(nums[dq.front()]);
        
        return answer;    
    }
    
};
```

![LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled%201.png](LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled%201.png)

![LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled%202.png](LeetCode%20239%20Sliding%20Window%20Maximum%20a0d4ab2c41304d2bb9083ed9f18fb1ed/Untitled%202.png)