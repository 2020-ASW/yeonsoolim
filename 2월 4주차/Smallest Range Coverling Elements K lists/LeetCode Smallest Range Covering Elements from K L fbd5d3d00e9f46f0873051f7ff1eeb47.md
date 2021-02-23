# LeetCode Smallest Range Covering Elements from K Lists

# Problem

You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

→ 오름 차순으로 여러개의 vector들이 주어진다.

→ vector들 모두 1개 이상씩 포함하는 가장 작은 범위를 구하라.

# Solve

1. 모든 원소들을 합쳐준다.
    - set을 이용하면 O(N)만에 merge된 배열을 구할 수 있다.
    but, set에서 구간의 정보를 구하기위해 iter = set.begin() + left 를 했으나, set의 iterator는 const라서 안되는 것 같다.
    - vector에 원소를 넣은 뒤, O(NlogN) 정렬을 하여 사용한다.

    ```cpp
     void mergeAll(vector<vector<int>> &nums){
    	  for(int i=0; i<nums.size(); i++){
    	      for(auto &num : nums[i]){
    	          all.push_back({num, i+1});
    	      }
    	  }
    	  sort(all.begin(), all.end());
    }
    ```

2. left = 0, right = 0 부터 twopointer를 이용하여 탐색한다.
    1. [ left, right ] 의 범위가 모든 group에서 1개씩 만족하는 가 를 check 하기 위한 조건으로 아래를 사용했으나, 시간 초과. 매번 left~right를 보니 확실히 오래 걸린다.

        ```cpp
        bool check(int left, int right){
            bitset <3502> bit;
            for(int i=left; i<=right; i++){
               // cout << all[i].first<<' '<<all[i].second<<'\n';
                bit.set(all[i].second);
            }
            if(bit.count() == kind) return true;
            else return false;        
        }
        ```

    2. 하나의 bitset만 사용하여 left가 증가 할 때는 체크 후 reset해주고, right가 증가 할 때는 체크 후 set하는 방식을 사용한다.
        - all 배열은 값과 그 값이 해당하는 그룹이 들어있다.  { num, i+1 } : pair<int,int>   // 그룹은 1부터 시작.
        - < left++ >   `if(kind[all[left].second] == 0) bit.reset(all[left].second);`

            빠져나올 값의 group이 변경 될 범위에도 있다면 그대로 
            빠져나올 값이 유일했다면 reset

        - < right++ >  `if(kind[all[right].second] == 1) bit.set(all[right].second);`

            추가될 값이 새로 인식되는 group이라면 set
            추가될 값이 이미 있는 group이라면 그대로

3. 끝까지 범위를 조사해서 가장 최소의 구간 (right-left+1이 작은 것) 을 구한다.

# Code

```cpp
class Solution {
public:
    vector <pair<int,int> > all;
    vector <int> kind;
    
    void mergeAll(vector<vector<int>> &nums){
        for(int i=0; i<nums.size(); i++){
            for(auto &num : nums[i]){
                all.push_back({num, i+1});
            }
        }
        sort(all.begin(), all.end());
    }
    
    bool check(bitset <3502> &bit, int left, int right){
        if(bit.count() == kind.size()-1) return true;
        return false;
    }

    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> answer;
        pair<int,int> resultPair;
        int resultSize = 2147483647;
        
        kind.resize(nums.size()+1);
        mergeAll(nums);    
        bitset <3502> bit;
        int left = 0, right = 0;
        bit.set(all[left].second);
        kind[all[left].second]++;

        while(left < all.size()){
            if(check(bit, left, right)){
                int lv = all[left].first;
                int rv = all[right].first;
                int diff = abs(rv-lv)+1;
                
								if(resultSize > diff){
                    resultPair = {lv, rv};
                    resultSize = diff;
                    if(diff == 1) break;
                }
                
                kind[all[left].second]--;
                if(kind[all[left].second] == 0) bit.reset(all[left].second);
                left++;
            }else{
                right++;
                if(right>=all.size()) break;
                kind[all[right].second]++;
                if(kind[all[right].second] == 1) bit.set(all[right].second);
            }
            if(left>right) break;
            if(right>=all.size())break;
        }
        answer.push_back(resultPair.first);
        answer.push_back(resultPair.second);
        return answer;
    }
};
```