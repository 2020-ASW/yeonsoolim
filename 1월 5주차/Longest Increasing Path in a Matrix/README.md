# LeetCode 329 Longest Increasing Path in a Matrix

# memorization

# Pre

- 작은 원소부터 경로를 체크한다.
- 4방향에 대한 DP

# Error

- 4 방향에 대한 DP ⇒ 어렵다.
- 일단 그냥 경로를 체크해보자.

    ```cpp
    void search(int x, int y, int depth, vector<vector<int>>& matrix){
        answer = (depth > answer ? depth : answer);
        
        for(int d=0; d<4; d++){
            int nextX = dx[d]+x;
            int nextY = dy[d]+y;
            if(inner(nextX, nextY)) continue;
            if(matrix[nextY][nextX] <= matrix[y][x]) continue;
            visit[nextY][nextX] = true;
            search(nextX, nextY, depth+1, matrix);
            visit[nextY][nextX] = false;
        }
    }
    ```

    ⇒ 2차원 배열 최대 200 * 200
        대충 40000개에서 다 돌고 4방향 ⇒ 40억

# Solve

- **작은 곳 부터 돌아서 memorization을 효율적으로 사용하게 한다.**

    ```cpp
    static bool cmp(const Coord &a, const Coord &b){
        return a.val < b.val;
    }
    sort(smallCoord.begin(), smallCoord.end(), cmp);
            
    for(auto &point : smallCoord){
        visit[point.y][point.x] = true;
        search(point.x, point.y, 1, matrix);
        visit[point.y][point.x] = false;

    }
    ```

- **Memorization을 이용해 지나간 길 중 큰 값은 가지말자.**
- **길의 저장된 값이 크다면? 현재 depth를 가지고 갈 필요가 없다.**

    **길의 저장된 값이 작다면? 현재 depth가 더 크니까 가봐야 한다. (저장후)**

    ```cpp
    if(memory[y][x]>depth) return;
    else memory[y][x] = depth;
    ```

- **search 시에도 depth가 큰 곳은 가지 않는다.**

    ```cpp
    void search(int x, int y, int depth, vector<vector<int>>& matrix){
            
        if(memory[y][x]>depth) return;
        else memory[y][x] = depth;
        answer = (depth > answer ? depth : answer);
        
        for(int d=0; d<4; d++){
            int nextX = dx[d]+x;
            int nextY = dy[d]+y;
            
    				if(inner(nextX, nextY)) continue;
            if(matrix[nextY][nextX] <= matrix[y][x]) continue;
            if(memory[nextY][nextX] > depth+1) continue;
            
    				visit[nextY][nextX] = true;
            search(nextX, nextY, depth+1, matrix);
            visit[nextY][nextX] = false;
        }
    }
    ```

# Post

- sort안하는게 더 빠르다,,,,

# Code

```cpp
struct Coord{
    int x;
    int y;
    int val;
};
class Solution {   
public:
    int X, Y, answer;
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    vector <vector <bool> > visit;
    vector <vector <int> > dp;
    vector <Coord> smallCoord;
    
    static bool cmp(const Coord &a, const Coord &b){
        return a.val < b.val;
    }
    
    bool inner(int x, int y){
        return !(0<=x&&x<X && 0<=y && y<Y);
    }
        
    void search(int x, int y, int depth, vector<vector<int>>& matrix){
        
        if(dp[y][x]>depth) return;
        else dp[y][x] = depth;
        answer = (depth > answer ? depth : answer);
        
        for(int d=0; d<4; d++){
            int nextX = dx[d]+x;
            int nextY = dy[d]+y;
            if(inner(nextX, nextY)) continue;
            if(matrix[nextY][nextX] <= matrix[y][x]) continue;
            if(dp[nextY][nextX] > depth+1) continue;
            visit[nextY][nextX] = true;
            search(nextX, nextY, depth+1, matrix);
            visit[nextY][nextX] = false;
        }
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        answer = 0;
        Y = matrix.size();
        X = matrix[0].size();
        visit.resize(Y);
        dp.resize(Y);
        for(int i=0; i<Y; i++){
            visit[i].resize(X);
            dp[i].resize(X);
            for(int j=0; j<X; j++){
                smallCoord.push_back({j,i,matrix[i][j]});
            }
        }
        sort(smallCoord.begin(), smallCoord.end(), cmp);
        
        for(auto &point : smallCoord){
            visit[point.y][point.x] = true;
            search(point.x, point.y, 1, matrix);
            visit[point.y][point.x] = false;

        }
        return answer;
        
    }
};
```

![LeetCode%20329%20Longest%20Increasing%20Path%20in%20a%20Matrix%204f9d626f48554e7fa9b4ad28d5e80252/Untitled.png](LeetCode%20329%20Longest%20Increasing%20Path%20in%20a%20Matrix%204f9d626f48554e7fa9b4ad28d5e80252/Untitled.png)