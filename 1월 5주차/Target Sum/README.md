# LeetCode 494 Target sum

# recurrsive

# Pre

- 재귀로 경우의 수를 고려해 음수 취급을 하면서 더하자.
- bitmask를 체크하면 음수 체크 안되있으면 양수.
- bitmask는 0과 1밖에 없고 default가 0이라서 음수로 갔던 곳만 체크할 수 있다.

    ?? : if(bit.test(0) == 0) 이면 양수로 간다면?

    → 어쨋든 양쪽다 갈 수가 없다.

    ```cpp
    if(bit.test(next)){
        bit.reset(next);
        search(next, nums, bit);
        bit.set(next);
    }else{
        bit.set(next);
        search(next, nums, bit);
        bit.reset(next);
    }
    ```

# Error

- **Overflow :**

    [2,107,109,113,127,131,137,3,2,3,5,7,11,13,17,19,23,29,47,53]
    2147483647

    ⇒ long long 사용

- **N과 M 을 다시 풀어야겠다.**

# Code

```cpp
#define ll long long
class Solution {
public:
    int answer;

    void search(int cur, vector<int>& nums, ll sum){
        if(cur == nums.size()-1){
            if(sum == 0){
                answer++;  
            } 
            return;
        }
        search(cur+1, nums, sum-nums[cur+1]);
        search(cur+1, nums, sum+nums[cur+1]);
    }
    
    int findTargetSumWays(vector<int>& nums, int S) {
        answer = 0;
        search(-1, nums, (ll)S);    
        return answer;
    }
};
```