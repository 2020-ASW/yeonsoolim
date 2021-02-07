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
int dx[5] = { 1, 0, -1, 0 };
int dy[5] = { 0, 1, 0, -1 };
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
        if (answerCore <= coreSum) {
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
            if (cores.size() - (depth)+coreSum < answerCore)continue;
            dfs(depth + 1, sum, coreSum);
        }
        else {
            dfs(depth + 1, sum + result, coreSum + 1);
        }
        copy(temp.begin(), temp.end(), visit.begin());
    }
    if (wall == 4) dfs(depth + 1, sum, coreSum);
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