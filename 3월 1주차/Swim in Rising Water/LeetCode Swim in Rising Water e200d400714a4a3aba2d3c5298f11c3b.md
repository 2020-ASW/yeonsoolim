# LeetCode Swim in Rising Water

# Problem

- 좌표(0,0)에서 → 좌표(N-1, N-1)까지 가는데, 제약이 있다.
- 해당 좌표 값의 시간이 지나야 지나갈 수 있다.
- 가장 최소의 시간 만에 도착하도록 해야 한다.

# Pre

- 너무 어렵게 생각했다. Priority_Queue를 사용하게 되면 알아서 주변 값 중 가장 작은 시간을 가진 경로를 따라 갈텐데,
시간을 계산하는 식을 넣어버려서 특성을 살리지 못한 코드를 만들었다.

    ![LeetCode%20Swim%20in%20Rising%20Water%20e200d400714a4a3aba2d3c5298f11c3b/Untitled.png](LeetCode%20Swim%20in%20Rising%20Water%20e200d400714a4a3aba2d3c5298f11c3b/Untitled.png)

# Solve

- 단순히 PriorityQueue로 BFS를 하게 되면, 
PQ는 가장 작은 주변의 시간을 따라 갈거고,
BFS는 최단 거리로 도착하게 만들 것이다.

# Code

```cpp
class Solution {
public:
    struct info{
        int time;
        int x;
        int y;
    };
    struct cmp{
        bool operator()(const info &a, const info &b){
            return a.time > b.time;
        }
    };
    int N;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int visit[51][51];
    int startTime, endTime;
    priority_queue <info, vector<info>, cmp> pq;
    void init(){
        for(int i=0; i<51; i++){
            for(int j=0; j<51; j++){
                visit[i][j] = 0;
            }
        }
    }
    bool OOR(int x, int y){
        return !(0<=x && x<N && 0<=y && y<N);
    }
    int swimInWater(vector<vector<int>>& grid) {
        init();
        N = grid.size();
        startTime = grid[0][0];
        endTime = grid[N-1][N-1];

        pq.push({startTime, 0, 0});
        visit[0][0] = startTime;
        int answer = grid[0][0];
        while(!pq.empty()){
            info curr = pq.top(); pq.pop();
            answer = max(answer, curr.time);
            if(curr.x == N-1 && curr.y == N-1) break;
            for(int d=0; d<4; d++){
                int next_x = curr.x+dx[d];
                int next_y = curr.y+dy[d];

                if(OOR(next_x, next_y)) continue;
                if(visit[next_y][next_x]) continue;
                
                visit[next_y][next_x] = grid[next_y][next_x];
               
                pq.push({grid[next_y][next_x], next_x, next_y});
            }
        }
        return answer;
    }
};
```