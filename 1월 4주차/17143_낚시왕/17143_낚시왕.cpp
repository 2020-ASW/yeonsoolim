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