# LeetCode 378 Kth Smallest Element in a Sorted Matrix

# sort # Priority_queue

# 문제

Given an `n x n` `matrix` where each of the rows and columns are sorted in ascending order, return *the* `kth` *smallest element in the matrix*.

Note that it is the `kth` smallest element **in the sorted order**, not the `kth` **distinct** element.

# Pre

## 수학적 접근

k / rowSize , k % rowSize, k / colSize, k % colSize 등을 이용하여 O(1)만에 접근 하는 방법.

## 반례

[[1,2],[1,3]] 에 의해 해당 되지 않음.

# Solve

1. **Priority_Queue를 이용하여 모든 수를 정렬해준다.**
( 300 X 300 이기 때문에 가능 )

    ```cpp
    priority_queue <int, vector<int>, greater<int>> pq;
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            pq.push(matrix[i][j]);
        }
    }
    ```

2. **index 접근이 안되므로, cnt 가 k 될 때까지 돌아본다.**
( k는 90,000 이하 )

    ```cpp
    int cnt = 0;
    while(!pq.empty()){
        int now = pq.top(); pq.pop();
        if(++cnt == k)
            return now;
    }
    ```

# Code

```cpp
class Solution {
public:
    
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        
        priority_queue <int, vector<int>, greater<int>> pq;
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[i].size(); j++){
                pq.push(matrix[i][j]);
            }
        }
        
        int cnt = 0;
        while(!pq.empty()){
            int now = pq.top(); pq.pop();
            //cout << now <<' ';
            if(++cnt == k)
                return now;
        }
        return -1;
    }
};
```

![LeetCode%20378%20Kth%20Smallest%20Element%20in%20a%20Sorted%20Matr%20d764dfa45575499f985f4f23cd54bb73/Untitled.png](LeetCode%20378%20Kth%20Smallest%20Element%20in%20a%20Sorted%20Matr%20d764dfa45575499f985f4f23cd54bb73/Untitled.png)