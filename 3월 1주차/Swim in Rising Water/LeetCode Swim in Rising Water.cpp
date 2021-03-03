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