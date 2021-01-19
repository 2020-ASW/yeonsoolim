# 17143_낚시왕

simulation

# Pre

1. 순서대로 구현을 하면 될 것 같다.
    1. 낚시왕이 이동.
    2. 땅과 제일 가까운 상어 낚시.
    3. 상어 이동
2. 주의 사항
    1. 낚시왕이 이동 
        - 끝 도달 시 정지 + (C+1) 의 Index가 필요.
    2. 상어 낚시
        - 상어가 사라지는 것 잊지말고 처리.
        - 상어가 없으면?
    3. 상어 이동
        - 상어는 속도 & 방향 & 크기가 있다.
        → struct
        - 벽 갔다가 반대로 가야한다.
        - 상어 끼리 만나면 큰 상어만 남고 작은 상어 삭제

# Error

1. 벽 충돌 시
    - 왼쪽, 위쪽 벽 충돌 시 기준점이 1이다.
    - 오른쪽, 아래쪽 벽 충돌 시 기준점이 C,R 이다.
2. 벽을 여러 번 충돌 할 수 있다.
    - 1이하 음수일 때, R,C 초과 큰 수 일 때 계속.
3. 상어가 동시에 만나야 한다.

# Solve

1. **순서대로 구현을 하면 될 것 같다.**
    1. **낚시왕이 이동.**

        ```cpp
        struct King {
        	int r;
        	int c;
        	int getShark;
        };
        ```

        ```cpp
        void kingMove() {
        	if (++king.c == C + 1) {
        		cout << king.getShark;
        		exit(0);
        	}
        }
        ```

    2. **땅과 제일 가까운 상어 낚시.**
    한 마리만 잡는다

        ```cpp
        void sharkCatch() {
        	for (int i = 1; i <= R; i++) {
        		if (base[i][king.c].size == 0) continue;
        		king.getShark += base[i][king.c].size;
        		base[i][king.c] = { 0,0,0 };
        		**return;**
        	}
        }
        ```

    3. **상어 이동**

        ```cpp
        void sharkMove() {
        		
        }
        ```

2. **주의 사항**
    1. **낚시왕이 이동** 
        - 끝 도달 시 정지 + (C+1) 의 Index가 필요.
        ⇒ 땅을 넉넉하게  0~ C+2를 가지도록 선언.
    2. **상어 낚시**
        - 상어가 사라지는 것 잊지말고 처리.
        ⇒ 잡아먹혀도 사라지고,
        ⇒ 낚시당해도 사라짐.
        - 상어가 없으면?
        ⇒ 안잡고 넘어가면됨.
    3. **상어 이동**
        - 상어는 속도 & 방향 & 크기가 있다.
        → struct
        - 벽 갔다가 반대로 가야한다.
            1. **벽 충돌 시**
                - 왼쪽, 위쪽 벽 충돌 시 기준점이 1이다.
                - 오른쪽, 아래쪽 벽 충돌 시 기준점이 C,R 이다.
            2. **벽을 여러 번 충돌 할 수 있다.**
                - 1이하 음수일 때, R,C 초과 큰 수 일 때 계속.

            - return 할 값 :  바뀔 x좌표, 바뀔 y좌표, 충돌 횟수
            - 음수 일때는 기준 좌표가 1이고 음수기 때문에 abs 및 +2처리
            - 양수 일때는 벽으로 부터 떨어진 크기를 구해야함.
            - while 범위를 만족하지 않는 것은 충돌 대사

            ```cpp
            vector <int> wallCrash(int x, int y, int d, int s) {
            	vector <int> res(3, 0);
            	int next_x = dx[d]* s + x;
            	int next_y = dy[d]* s + y;
            	while (!(1 <= next_x && next_x <= C && 1 <= next_y && next_y <= R)) {
            		res[2]++;
            		if (next_x <= 0) {
            			next_x = (abs(next_x) + 2);
            		}
            		else if (next_y <= 0) {
            			next_y = (abs(next_y) + 2);
            		}
            		else if (next_x > C) {
            			next_x = 2 * C - next_x;
            		}
            		else if (next_y > R) {
            			next_y = 2 * R - next_y;
            		}
            	}
            	res[0] = next_x;
            	res[1] = next_y;
            	return res;
            }
            ```

        - 상어 끼리 만나면 큰 상어만 남고 작은 상어 삭제
3. **상어가 동시에 만나야 한다.**

    ```cpp
    Shark newShark = base[i][j];
    ...
    Shark preShark = changeBase[res[1]][res[0]];
    if (있으면 큰거) {
    		Shark preShark = changeBase[res[1]][res[0]];
    		changeBase[res[1]][res[0]] = (newShark.size > preShark.size ? newShark : preShark);
    	}
    else  없으면 대입
    		changeBase[res[1]][res[0]] = newShark;
    ```

# Code

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct King {
	int r;
	int c;
	int getShark;
};
struct Shark {
	int speed;
	int direct;
	int size;
};
int dx[5] = { 0, 0, 0, 1, -1 };
int dy[5] = { 0, -1, 1, 0, 0 };

int R, C, M, r, c, s, d, z;
King king = { 0,0,0 };
vector <vector<Shark> > base;
vector <vector<Shark> > changeBase;

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> R >> C >> M;
	if (M == 0) cout << "0", exit(0);
	base.resize(R + 1); for (auto& tmp : base) tmp.resize(C + 2);
	//changeBase.resize(R + 1); for (auto& tmp : changeBase) tmp.resize(C + 2);
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		base[r][c] = { s, d, z };
	}
}
void print() {
	cout << '\n';
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << base[i][j].size << ' ';
		}cout << '\n';
	}cout << '\n';
}
vector <int> wallCrash(int x, int y, int d, int s) {
	vector <int> res(3, 0);
	int next_x = dx[d]* s + x;
	int next_y = dy[d]* s + y;
	while (!(1 <= next_x && next_x <= C && 1 <= next_y && next_y <= R)) {
		res[2]++;
		if (next_x <= 0) {
			next_x = (abs(next_x) + 2);
		}
		else if (next_y <= 0) {
			next_y = (abs(next_y) + 2);
		}
		else if (next_x > C) {
			next_x = 2 * C - next_x;
		}
		else if (next_y > R) {
			next_y = 2 * R - next_y;
		}
	}
	res[0] = next_x;
	res[1] = next_y;
	return res;
}
int reverseD(int d, int cnt) {
	if (cnt % 2 == 0) return d;
	else return (d % 2 == 0 ? (d - 1) : (d + 1));
}
void kingMove() {
	if (++king.c == C + 1) {
		cout << king.getShark;
		exit(0);
	}
}
void sharkCatch() {
	for (int i = 1; i <= R; i++) {
		if (base[i][king.c].size == 0) continue;
		king.getShark += base[i][king.c].size;
		base[i][king.c] = { 0,0,0 };
		return;
	}
}
void sharkMove() {
	vector <int> res(3, 0);
	changeBase.resize(R + 1); for (auto& tmp : changeBase) tmp.resize(C + 2);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (base[i][j].size == 0) continue;
			Shark newShark = base[i][j];
			res = wallCrash(j, i, base[i][j].direct, base[i][j].speed);
			newShark.direct = reverseD(newShark.direct, res[2]);

			if (changeBase[res[1]][res[0]].size != 0) {
				Shark preShark = changeBase[res[1]][res[0]];
				changeBase[res[1]][res[0]] = (newShark.size > preShark.size ? newShark : preShark);
			}
			else 
				changeBase[res[1]][res[0]] = newShark;
		}
	}
	copy(changeBase.begin(), changeBase.end(), base.begin());
	changeBase.clear();
}

int main() {
	input();
	while (1) {
		kingMove();
		sharkCatch();
		sharkMove();
	}
}
```

![17143_%E1%84%82%E1%85%A1%E1%86%A9%E1%84%89%E1%85%B5%E1%84%8B%E1%85%AA%E1%86%BC%20f9a28da3324447d59f0f9d84a213cd3b/17143_.png](17143_%E1%84%82%E1%85%A1%E1%86%A9%E1%84%89%E1%85%B5%E1%84%8B%E1%85%AA%E1%86%BC%20f9a28da3324447d59f0f9d84a213cd3b/17143_.png)