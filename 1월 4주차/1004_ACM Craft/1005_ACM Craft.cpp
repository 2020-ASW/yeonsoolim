#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;
int T, N, K, X, Y, W;
vector <int> towers;
vector <int> towersCnt;
vector <int> towerDelayed;
vector <vector<int> > dependency;
queue <pair<int, int> > q;

void initClear() {
	dependency.clear();
	towers.clear();
	towersCnt.clear();
	towerDelayed.clear();
	while (!q.empty()) q.pop();
}
void initResize() {
	towers.resize(N + 1);
	towersCnt.resize(N + 1);
	dependency.resize(N + 1);
	towerDelayed.resize(N + 1);
}

void tpsort() {
	for (int idx = 1; idx <= N; idx++) {
		towerDelayed[idx] = towers[idx];
		if (towersCnt[idx] == 0) {
			q.push({ idx, towers[idx] });
		}
	}

	while (!q.empty()) {
		pair<int, int> now = q.front(); q.pop();
		if (now.first == W)
			return;
		
		for (auto& next : dependency[now.first]) {
			towersCnt[next]--;
			int newDelayed = towerDelayed[now.first] + towers[next];
			int nextDelayed = towerDelayed[next];
			towerDelayed[next] = (nextDelayed < newDelayed ? newDelayed : nextDelayed);
			if (towersCnt[next] == 0)
				q.push({ next, now.second + towers[next] });
		}
	}
}


void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	while (T--) {
		initClear();
		cin >> N >> K;
		initResize();
		for (int i = 1; i <= N; i++) cin >> towers[i];
		for (int i = 0; i < K; i++) {
			cin >> X >> Y;
			dependency[X].push_back(Y);
			towersCnt[Y]++;
		}
		cin >> W;

		tpsort();
		cout << towerDelayed[W] << '\n';
	}
}

int main() {
	input();
}