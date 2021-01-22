# LeetCode 124 Binary Tree Maximum Path Sum

# 문제이해

- A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them.

    Path 는 시퀀스의 Node에서 인접한 각 쌍의 가장자리를 연결.

    시퀀스를 뭐라고 해석해야할까...

- A node can only appear in the sequence at most once. 
Note that the path does not need to pass through the root.

    Node는 한 번만.
    root를 안통과 해도 된다.

- 경로의 합 중 최대를 반환.

# Error

1.  **문제 이해**

    ![LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/Untitled.png](LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/Untitled.png)

    - Red 처럼 모든 곳을 연결해서 합을 구하는게 아니였다.
    - 갈래 길이 없이 그어지는 경로를 찾아야 했다.

2. **root 는 포함되지 않는, 중간에 어떤 경로에서만 최대값을 가질 수 있다.**

    **중간 최대값은 따로 저장해두어야 한다.**

    ![LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/Untitled%201.png](LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/Untitled%201.png)

# Solve 2 다시풀기

96 ms → 32 ms

only Left,  only Right 는 고려할 필요가 없다.

- 중간에 Return 하기전 최대가 될 수 있는 값은 mid + left + right

    ```java
    int currentMax = max(midLeftRight, max(mid, max(midLeft,midRight)));
    maximum = (maximum < currentMax ? currentMax : maximum);

    if(currentMax == midLeftRight) return max(midLeft,midRight);
    return currentMax;
    ```

- 그 이후에 Return 할 때는 무조건 mid가 포함되어야 하기 때문에
    1. mid + left

        ```java
         int midLeft = (now->left ? dfs(now->left) + mid : -2147483648);
        ```

    2. mid + right

        ```java
        int midRight = (now->right ? dfs(now->right) + mid : -2147483648);
        ```

    3. mid

        ```java
        int mid = now->v
        ```

    만 고려.

```java
#include <algorithm>
#define minimum -2147483648
class Solution {
public:
    int maximum;
    int dfs(TreeNode* now){
        
        int mid = now->val;
        int midLeft = (now->left ? dfs(now->left) + mid : -2147483648);
        int midRight = (now->right ? dfs(now->right) + mid : -2147483648);
        int midLeftRight = (now->left && now->right ? midLeft+midRight-mid : -2147483648);
        
        int currentMax = max(midLeftRight, max(mid, max(midLeft,midRight)));
        maximum = (maximum < currentMax ? currentMax : maximum);
        
        if(currentMax == midLeftRight) return max(midLeft,midRight);
        return currentMax;
    }
    
    int maxPathSum(TreeNode* root) {
        maximum = root->val;
        dfs(root);
        return maximum;
    }
};
```

# =====================끝

# ~~Solve~~

1. DFS를 쓸건데, 

    root에서는 left, right로 재귀를 하여 가장 큰 값들을 받아 올 것이다.

    - 가장 큰 값인지 확인해야하는 경우의 수
    1. ~~오직 Left 에서 오는 값.~~
    2. ~~오직 Right 에서 오는 값.~~
    3. 오직 현재 Mid 의 값.
    4. Mid 와 Left 값을 합친 값.
    5. Mid 와 Right 값을 합친 값.
    6. Mid 와 Left와 Right 값을 합친 값.
    - 주의

        max 로 비교할 때, 초기화 된 0 으로 비교하면 안된다. 음수 weight가 있기 때문. ⇒ -2147483648로 비교해주자.

        ```java
        if(now->left){
            left = dfs(now->left);  
            midLeft = left+mid;
        }else{
            left = -2147483648;
            midLeft = -2147483648;
        }

        if(now->right){
            right = dfs(now->right);
            midRight = right+mid;
        }else{
            right = -2147483648;
            midRight = -2147483648;
        }

        if(now->left && now->right){
            midLeftRight = left+mid+right;
        }else{
            midLeftRight = -2147483648;
        }
        ```

2. 여기 까지는 저장하되, return 하는 값은 반드시 Mid 가 포함되어야 한다.

    ```java
    int currentMax = max(midLeftRight, max(mid,max(left,max(midLeft,max(right,midRight)))));
    ```

    - mid, midLeft, midRight 는 그대로 반환.

        ```java
        if(currentMax == mid || currentMax == midRight || currentMax == midLeft){
            return currentMax;
        }
        ```

    - **midLeftRight는 Error 1 : 문제 이해에 의해 반환될 수 없다.**
    위와 같은 형태로 반환해야함.

        ```java
        else if(currentMax == midLeftRight){
            return max(midLeft,midRight);
        }
        ```

    - Left, Right 가 최대일 경우는 mid를 포함해서 return 해야한다.

        ```java
        else{
          return max(currentMax+mid, mid);  
        }
        ```

# Code

```java
#include <algorithm>
#define minimum -2147483648
class Solution {
public:
    int maximum;
    int dfs(TreeNode* now){
        int total = 0;
        
        int left = 0, midLeft = 0;
        int right = 0, midRight = 0;
        int midLeftRight = 0;
        int mid = now->val;
        if(now->left){
            left = dfs(now->left);  
            midLeft = left+mid;
        }else{
            left = -2147483648;
            midLeft = -2147483648;
        }
        
        if(now->right){
            right = dfs(now->right);
            midRight = right+mid;
        }else{
            right = -2147483648;
            midRight = -2147483648;
        }
        
        if(now->left && now->right){
            midLeftRight = left+mid+right;
        }else{
            midLeftRight = -2147483648;
        }
        
        int currentMax = max(midLeftRight, max(mid,max(left,max(midLeft,max(right,midRight)))));
        maximum = (maximum < currentMax ? currentMax : maximum);
        if(currentMax == mid || currentMax == midRight || currentMax == midLeft){
            return currentMax;
        }else if(currentMax == midLeftRight){
            return max(midLeft,midRight);
        }else{
          return max(currentMax+mid, mid);  
        } 
    }
    
    int maxPathSum(TreeNode* root) {
        maximum = root->val;
        dfs(root);
        return maximum;
    }
};
```

![LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/PNG__4.png](LeetCode%20124%20Binary%20Tree%20Maximum%20Path%20Sum%20b9c425902a984d87b59e62f95bca7dc1/PNG__4.png)