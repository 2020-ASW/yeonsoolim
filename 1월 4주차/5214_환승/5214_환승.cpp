#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;
int N, K, M;

struct Terminal {
	int idx;
	int cnt;
};

vector <vector<int> > allTerminals;
int visit[101001];
void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N >> K >> M;
	//terminals.resize(N);
	//hypertubes.resize(M);
	allTerminals.resize((int)N + M + 1);  // 0~N-1, N ~ N+M-1
	for (int i = N; i< N+M; i++) {
		for (int j = 0; j < K; j++) {
			int temp;
			cin >> temp;
			allTerminals[i].push_back(temp - 1);
			allTerminals[temp - 1].push_back(i);
		}
	}
}

int main() {
	input();
	
	queue <Terminal> q;
	q.push({ 0, 1 });
	visit[0] = true;
	while (!q.empty()) {
		Terminal now = q.front(); q.pop();
		if (now.idx == N-1) {
			cout << now.cnt;
			exit(0);
		}

		for (auto& next : allTerminals[now.idx]) {
			if (visit[next]) continue;

			visit[next] = true;
			if (next >= N) q.push({ next, now.cnt });
			else q.push({ next, now.cnt + 1 });
		}
	}
	cout << "-1";
}