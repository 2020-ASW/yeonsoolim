# 1767 프로세서 연결하기

simulation

# Pre

1. 프로세서 순서가 중요할까?

    우선 순서를 고려해서 해보았지만, 갯수가 너무 많았다.

# Error

1. 첫 Core의 Idx를 0으로 매겨버렸다.
2. 시간 초과 : 

    ⇒ 미리 answerCore보다 안될 것 같으면 끊어줘야 한다.

    ```cpp
    if (cores.size() - (depth) + coreSum < answerCore)continue;
    ```

    ⇒ 가장 자리 이외에 안되는 것 계산.

    ```cpp
    if (preCore == (N * 2 + (N - 2) * 2)) {
        cout << "#" << test_case << ' ' << 0 << '\n';
        continue;
    }
    ```

3. **가장자리 Core에 대한 미리 계산.**

         < 잘못됨  : 중복이 있다.> 

    ```cpp
    for (int i = 0; i < N; i++) {
        if (boards[0][i] == 1) preCore++;
        if (boards[N - 1][i] == 1)preCore++;
        if (boards[i][0] == 1) preCore++;
        if (boards[i][N - 1] == 1) preCore++;
    }
    ```

    ```cpp
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
                if (boards[i][j] == 1) preCore++;
    ```

    중복이 없다.  입력 받을 때 계산을 해준다.

# Solve

1. 구하려는 것 : 전선의 최소 길이 

    → 전선이 0 필요한 가장자리 Core는 빼고 탐색.  (미리 입력 받을 때, 제외하고 받는다)

    ```cpp
    cin >> boards[i][j];
    if (i != 0 && i != N - 1 && j != 0 && j != N - 1 && boards[i][j] == 1)
        cores.push_back({ j,i,(int)cores.size() + 1 });
    ```

    → 조건을 만족할 때만, 전선의 길이 계산

    ```cpp
    if (next.x == 0 || next.x == N - 1 || next.y == 0 || next.y == N - 1) {
        switch (direction) {
        case 0:
            for (int i = x + 1; i <= next.x; i++) visit[y][i] = idx;
            break;
        case 1:
            for (int i = y + 1; i <= next.y; i++) visit[i][x] = idx;
            break;
        case 2:
            for (int i = x - 1; i >= next.x; i--) visit[y][i] = idx;
            break;
        case 3:
            for (int i = y - 1; i >= next.y; i--) visit[i][x] = idx;
            break;
        }

        return cnt;
    }
    ```

2. DFS 설계

    → visit 배열 관리

    미리 현재의 visit을 복사 한 뒤, 탐색 후 돌아올 때, 다시 원상 복귀

    ```cpp
    copy(visit.begin(), visit.end(), temp.begin());
        for (int d = 0; d < 4; d++) {
            
    				...  dfs() ...

            copy(temp.begin(), temp.end(), visit.begin());
    ```

    → Check  :  0, N-1 가장자리로 갈 수 있는지 확인 한 후, Core수, 전선 수를 늘릴지 체크 후 DFS

    ```cpp
        for (int d = 0; d < 4; d++) {
            int result = check(cores[depth].x, cores[depth].y, cores[depth].idx, d);
            if (result == 2147483647) {
                if (cores.size() - (depth) + coreSum < answerCore)continue;
                dfs(depth + 1, sum, coreSum);
            }
            else {
                dfs(depth + 1, sum + result, coreSum + 1);
            }
            copy(temp.begin(), temp.end(), visit.begin());
    ```

# Code

```cpp
#include<iostream>
#include <vector>
#include <algorithm>
#include <bitset>
 
using namespace std;
struct Coord {
    int x;
    int y;
    int idx;
};
int dx[5] = { 1, 0, -1, 0};
int dy[5] = { 0, 1, 0, -1};
vector <vector <int> > boards;
vector <vector <int> > visit;
vector <Coord> cores;
 
int N, T, answer, answerCore, preCore;
void boardsPrint() {
    for (auto& board : boards) {
        for (int i = 0; i < board.size(); i++) {
            cout << board[i] << ' ';
        }cout << '\n';
    }cout << '\n';
}
void visitPrint() {
    for (auto& board : visit) {
        for (int i = 0; i < board.size(); i++) {
            cout << board[i] << ' ';
        }cout << '\n';
    }cout << '\n';
    cout << "======================\n";
}
void coresPrint() {
    cout << cores.size() << '\n';
    for (auto& core : cores) {
        cout << core.x << ' ' << core.y << '\n';
    }
}
void input() {
    N = 0;
    cin >> N;
    boards.clear(); visit.clear(); cores.clear();
    answer = 2147483647; answerCore = 0; preCore = 0;
    boards.resize(N, vector<int>(N, 0));
    visit.resize(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> boards[i][j];
            if (i != 0 && i != N - 1 && j != 0 && j != N - 1 && boards[i][j] == 1)
                cores.push_back({ j,i,(int)cores.size() + 1 });
 
            if (i == 0 || j == 0 || i == N - 1 || j == N - 1) {
                if (boards[i][j] == 1) preCore++;
            }
        }
    }
 
}
bool outOfRange(Coord now) {
    return !(0 <= now.x && now.x < N && 0 <= now.y && now.y < N);
}
int check(int x, int y, int idx, int direction) {
    int cnt = 0;
    Coord next = { x,y };
 
    while (++cnt) {
        next = { next.x + dx[direction] , next.y + dy[direction] };
        if (outOfRange(next)) break;
        if (visit[next.y][next.x]) break;
        if (boards[next.y][next.x]) break;
        if (next.x == 0 || next.x == N - 1 || next.y == 0 || next.y == N - 1) {
            switch (direction) {
            case 0:
                for (int i = x + 1; i <= next.x; i++) visit[y][i] = idx;
                break;
            case 1:
                for (int i = y + 1; i <= next.y; i++) visit[i][x] = idx;
                break;
            case 2:
                for (int i = x - 1; i >= next.x; i--) visit[y][i] = idx;
                break;
            case 3:
                for (int i = y - 1; i >= next.y; i--) visit[i][x] = idx;
                break;
            }
 
            return cnt;
        }
    }
    return 2147483647;
}
 
 
void dfs(int depth, int sum, int coreSum) {
    if (depth >= cores.size()) {
        if (answerCore <= coreSum){
            if (answerCore < coreSum) {
                answer = sum; answerCore = coreSum;
            }
            else if (answerCore == coreSum) {
                answer = min(answer, sum);
            }
        }
        return;
    }
    vector <vector <int> > temp;
    temp.resize(N, vector<int>(N, 0));
    copy(visit.begin(), visit.end(), temp.begin());
    int wall = 0;
    for (int d = 0; d < 4; d++) {
         
        if (outOfRange({ cores[depth].y + dy[d], cores[depth].x + dx[d] })) continue;
        if (visit[cores[depth].y + dy[d]][cores[depth].x + dx[d]]) {
            wall++;
            continue;
        }
        if (boards[cores[depth].y + dy[d]][cores[depth].x + dx[d]]) {
            wall++;
            continue;
        }
 
        int result = check(cores[depth].x, cores[depth].y, cores[depth].idx, d);
        if (result == 2147483647) {
            if (cores.size() - (depth) + coreSum < answerCore)continue;
            dfs(depth + 1, sum, coreSum);
        }
        else {
            dfs(depth + 1, sum + result, coreSum + 1);
        }
        copy(temp.begin(), temp.end(), visit.begin());
    }
    if(wall == 4) dfs(depth + 1, sum, coreSum);
}
 
int main(int argc, char** argv)
{
    T = 0;
    cin >> T;
 
    for (int test_case = 1; test_case <= T; ++test_case) {
        input();
 
        if (preCore == (N * 2 + (N - 2) * 2)) {
            cout << "#" << test_case << ' ' << 0 << '\n';
            continue;
        }
        dfs(0, 0, 0);
        cout << "#" << test_case << ' ' << answer << '\n';
 
    }
    return 0;
}
```