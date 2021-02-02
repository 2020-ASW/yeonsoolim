# LeetCode 300 Longest Increasing Subsequence

# 문제이해

![LeetCode%20300%20Longest%20Increasing%20Subsequence%20f8cf89467d0a43b1bdddd6ffcdcc9a05/Untitled.png](LeetCode%20300%20Longest%20Increasing%20Subsequence%20f8cf89467d0a43b1bdddd6ffcdcc9a05/Untitled.png)

- 주어진 배열에서 LIS를 구하는 방식.
- DP로 풀수도 있으나, Follow up:  nlogn 에 의해 LIS로 풀이.

[LIS (Longest Increasing Subsequence)](https://www.notion.so/LIS-Longest-Increasing-Subsequence-4f84c24009564725b54d4b71b4e6a314)

# Solve

![LeetCode%20300%20Longest%20Increasing%20Subsequence%20f8cf89467d0a43b1bdddd6ffcdcc9a05/Untitled%201.png](LeetCode%20300%20Longest%20Increasing%20Subsequence%20f8cf89467d0a43b1bdddd6ffcdcc9a05/Untitled%201.png)

## BinarySearch

- LIS의 배열을 가장 최소로 유지시키기 위해 필요한 INDEX를 제공해 줄 수 있어야 한다.

```cpp
int binarySearch(int x){
    int left = 0, right = lis.size();
    int idx = 0;
    while(left<=right){
        int mid = (right - left) /2 + left;
        
        if(lis[mid] == x){
            return mid;
        }else if(lis[mid] < x){
            left = mid+1;
        }else if(lis[mid] > x){
            right = mid-1;
            idx = mid;
        }
    }
    return idx;
}
```

## LIS

- 한 원소씩 배열을 돌면서, LIS의 크기를 늘릴지, LIS의 값을 바꿀지를 결정한다.

```cpp
int lengthOfLIS(vector<int>& nums) {
		lis.push_back(-100000);
		for(int i=0; i<nums.size(); i++){
		    int now  = nums[i];  
		    if(lis[lis.size()-1] < now){
		        lis.push_back(now);
		    }else if(lis[lis.size()-1] > now){
		        lis[binarySearch(now)] = now;
		    }
		    
		}
		for(int i=0; i<nums.size(); i++){
		    cout << lis[i]<<' ';
		}
		return lis.size()-1;

}
```

# Code

```cpp
class Solution {
public:
    vector <int> lis;
    
    int binarySearch(int x){
        int left = 0, right = lis.size();
        int idx = 0;
        while(left<=right){
            int mid = (right - left) /2 + left;
            
            if(lis[mid] == x){
                return mid;
            }else if(lis[mid] < x){
                left = mid+1;
            }else if(lis[mid] > x){
                right = mid-1;
                idx = mid;
            }
        }
        return idx;
    }
    
    int lengthOfLIS(vector<int>& nums) {
        lis.push_back(-100000);
        for(int i=0; i<nums.size(); i++){
            int now  = nums[i];  
            if(lis[lis.size()-1] < now){
                lis.push_back(now);
            }else if(lis[lis.size()-1] > now){
                lis[binarySearch(now)] = now;
            }
            
        }
        for(int i=0; i<nums.size(); i++){
            cout << lis[i]<<' ';
        }
        return lis.size()-1;
        
    }
};
```