# LeetCode 45 Jump Game II

---

# Pre

- Binary Search

    몇 번 만에 갈 수 있는가?  left / right 증,감분을 알 수가 없다.

- Two Pointer

    구간의 합으로 해결이 될까? 건너뛰는게 너무 많다.

- DP

    미리 갈 수 있는 곳이 있다면 몇 번만에 왔는지 저장을 해놓는다.

# Solve

- **min값을 구하기 위해 D[]에 INTMAX를 넣어준다.**

    ```cpp

    ```

- **현재 위치 curr에서 갈 수 있는 곳은 nums[curr+next] 까지.
next를 변화시키면서 모든 곳에 최소 점프 수를 갱신해준다.**

    ```cpp
    for(int curr = 0; curr<nums.size()-1; curr++){

      // curr에서 도달 가능한 범위.
      for(int next = 1; next<=nums[curr];next++){ 

    			//저장되있는 것 vs 지금 뛰는것+1
          D[curr+next] = min(D[curr]+1,D[curr+next]); 
          if(curr+next >= nums.size()-1) {
              break;
              curr=nums.size();
          }
      }
    }
    ```

# ~~Code1~~

```cpp
class Solution {
public:
    int D[30001];
    int jump(vector<int>& nums) {
        fill(D+1, D+30001, 2147483647);
        
        for(int curr = 0; curr<nums.size()-1; curr++){
            for(int next = 1; next<=nums[curr];next++){ // curr에서 도달 가능한 범위.
                D[curr+next] = min(D[curr]+1,D[curr+next]); //저장되있는 것 vs 지금 뛰는것+1
                if(curr+next >= nums.size()-1) {
                    break;
                    curr=nums.size();
                }
            }
        }
        
        return D[nums.size()-1];   
    }
};
```

# Error

- **curr 이 1칸 씩 움직이니까 시간초과가 걸린다.**

    분명 curr을 뛰어넘을 수가 있다.

    1. curr보다 큰 값을 가지는 칸.
    2. curr 범위가 끝나는 칸.

    ```cpp
     next=1;
    while(curr+next < nums.size()){
        if(next >= nums[curr]) break;
        if(curr+next > nums.size()-1) break;
        next++;
    } 
    curr += next-1;
    ```

    **⇒ 정답이 조금 다르게 나온다. 덜 보는 곳이 있기 때문**

    너무 많이 jump 하므로 더 줄여줘야 한다.

- **어디까지 갈 수 있나?**

    ![LeetCode%2045%20Jump%20Game%20II%209efad76d87564e51b21a4aee35d86a78/Untitled.png](LeetCode%2045%20Jump%20Game%20II%209efad76d87564e51b21a4aee35d86a78/Untitled.png)

curr : 현재 위치  ⇒ nums[curr] + curr  :  방금 봤던 최대 거리.

next : 다음 위치 ⇒ nums[curr+next] + curr + next  :  다음 위치가 갈 수 있는 최대 거리.

적절한 앙상블

```cpp
next=1;
while(curr+next < nums.size() && nums[curr]+curr >= nums[curr+next]+curr+next){
    if(next >= nums[curr]) break;
    if(curr+next > nums.size()-1) break;
    next++;
} 
curr += next-1;  //++curr 이 위에 있음.
```

# Code 2

```cpp
class Solution {
public:
    int D[30001];
    int jump(vector<int>& nums) {
        fill(D+1, D+30001, 2147483646);
        
        for(int curr = 0; curr<nums.size()-1; curr++){
            int next;
            cout << curr<<' '<<nums[curr]<<'\n';
            for(next = 1; next<=nums[curr];next++){ // curr에서 도달 가능한 범위.
                D[curr+next] = min(D[curr]+1,D[curr+next]); //저장되있는 것 vs 지금 뛰는것+1
                if(curr+next >= nums.size()-1) {
                    break;
                    curr=nums.size();
                }
            }
            next=1;
            while(curr+next < nums.size() && nums[curr]+curr >= nums[curr+next]+curr+next){
                if(next >= nums[curr]) break;
                if(curr+next > nums.size()-1) break;
                next++;
            } 
            curr += next-1;
        }
        
        return D[nums.size()-1];   
    }
};
```

![LeetCode%2045%20Jump%20Game%20II%209efad76d87564e51b21a4aee35d86a78/PNG__10.png](LeetCode%2045%20Jump%20Game%20II%209efad76d87564e51b21a4aee35d86a78/PNG__10.png)