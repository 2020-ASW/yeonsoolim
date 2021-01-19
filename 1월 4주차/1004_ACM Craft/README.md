# 1005_ACM Craft

# queue # topological sort #위상 정렬

[Topological Sort (위상 정렬)](Topological%20Sort%20(%E1%84%8B%E1%85%B1%E1%84%89%E1%85%A1%E1%86%BC%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%85%E1%85%A7%E1%86%AF)%20e25c6ffc7deb405a8736f84f3d42de06.md)

# Pre

위상정렬을 이용.

1. Cycle이 없는 뻗어나가는 단방향이여야 함.
2. 특정 건물을 짓기 위해서 다른 건물이 꼭 필요하므로 줄을 세워주어야 함. ⇒ 위상정렬
3. 최대 1,000개 건물 * 최대 100,000 시간 ⇒ 1,000,000,000

**Topological Sort로 모든 Delay 후 W까지의 시간을 구한다.**

# Error

1. Delay시간을 어떻게 해야할까?

![1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/Untitled.png](1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/Untitled.png)

1. **set을 이용한 Level 별 Delay 중 가장 큰 값 검사.**

    ```cpp
    if (timeCheck.find(now.second) != timeCheck.end())
      	timeCheck[now.second] = (timeCheck[now.second] > towers[now.first] ? timeCheck[now.second] : towers[now.first]);
    else 
    		timeCheck.insert({ now.second, towers[now.first] });
    ```

2. **~~delayed 전역 변수를 이용하여 가장 큰 값 검사.~~**

    ```cpp
    delayed = (delayed < newDelayed ? newDelayed : delayed);
    ```

⇒ 둘 다 어떤 단계인지 알 수 없다. 
     1 :  같은 단계에서만 된다.
     2 :  모든 단계에서 적용된다.

# Solve

**특정 단계에서 어떤 Delay를 쓸지 고를 수 있어야 한다.**

![1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/Untitled%201.png](1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/Untitled%201.png)

**towerDelayed[] :  방문한 적이 있다면 거쳐온 값을 저장한다.
 W에 도착하기 전까지는 모두 필요한 건물이므로, delay값이 큰 것으로 저장한다.**

```cpp
int newDelayed = towerDelayed[now.first] + towers[next];
int nextDelayed = towerDelayed[next];
towerDelayed[next] = (nextDelayed < newDelayed ? newDelayed : nextDelayed);
```

# Code

```cpp
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
```

![1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/1005_ACM_Craft.png](1005_ACM%20Craft%2005716de627c24db2abe3f1543e87bd18/1005_ACM_Craft.png)