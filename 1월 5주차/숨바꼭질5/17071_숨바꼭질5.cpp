#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;
bool visit[500001][2];
int N, K, answer=-1;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> K;
	if (N == K) {
		cout << "0";
		exit(0);
	}
}
bool inner(int next) {
	return (0 <= next && next <= 500000);
}
void getTimeSchedule() {
	int younger = K;
	int older = N;
	queue <int> q;
	q.push(older);
	visit[older][0];
	for (int s = 0; s <= 999; s++) {
		//cout << s << '\n';
		//cout << "younger : " << younger << '\n';
		int olderSize = q.size();
		while (olderSize--) {
			older = q.front(); q.pop();
			//cout << "older : " << older << '\n';
			if (older == younger || visit[younger][s % 2]) { //언니가 많이 움직였고 움직였던 장소.
				cout << s;
				exit(0);
			}

			int nextA = older + 1;
			int nextB = older - 1;
			int nextC = older * 2;
			int nextTime = s + 1;
			if (inner(nextA) && !visit[nextA][nextTime % 2]) {
				q.push(nextA);
				visit[nextA][nextTime%2] = true;
			}
			if (inner(nextB) && !visit[nextB][nextTime % 2]) {
				q.push(nextB);
				visit[nextB][nextTime % 2] = true;
			}
			if (inner(nextC) && !visit[nextC][nextTime%2]) {
				q.push(nextC);
				visit[nextC][nextTime % 2] = true;
			}
		}
		if (younger + s > 500000) {
			cout << "-1";
			exit(0);
		}
		younger = younger + (s+1);
	}
}

int main() {
	input();
	getTimeSchedule();
	
}