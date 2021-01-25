# 1167_트리의 지름

# 문제이해

트리의 지름을 구하라.

# Solution

트리의 지름 구하는 법

1. **root에서 가장 먼 node를 구한다.**
( 모든 node는 root가 될 수 있으므로, 아무데서나 하면 된다는 뜻 )
2. **그 node에서 가장 먼 node를 구한다.**
3. **두 node사이의 거리가 트리의 지름이다.**

![1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled.png](1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled.png)

# Solve

### DFS

![1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%201.png](1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%201.png)

### BFS

![1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%202.png](1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%202.png)

# Code dfs

```cpp
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;
int V, endNode, maxLength;
vector <vector<pair<int, int> > > nodes;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> V;
	nodes.resize(V+1);
	for (int i = 0; i < V; i++) {
		int vertex, edge, cost;
		cin >> vertex;
		while (1) {
			cin >> edge;
			if (edge == -1) break;
			cin >> cost;
			nodes[vertex].push_back({ edge,cost });
		}
	}
}

void dfsEndNode(int now, int length, bitset <100001> visit) {
	
	if (length > maxLength) {
		maxLength = length;
		endNode = now;
	}
	
	for (auto& next : nodes[now]) {
		if (visit.test(next.first)) continue;
		visit.set(next.first);
		dfsEndNode(next.first, length+next.second, visit.set(next.first));
		visit.reset(next.first);
	}
}

void getEndNode(int node) {
	maxLength = 0;
	bitset <100001> visit; visit.reset(); visit.set(node);
	dfsEndNode(node, 0, visit);
}

int main() {
	input();
	getEndNode(1);
	getEndNode(endNode);
	cout << maxLength;
}
```

# Code bfs

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
typedef struct {
	int point;
	int dis;
}xy;

vector <vector<xy>> v;

int V, ans, max_node, max_distance;
bool check[100001];
queue <xy> q;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> V;
	v.resize(V+1);
	for (int i = 0; i < V; i++) {
		int vertex, edge, cost;
		cin >> vertex;
		while (1) {
			cin >> edge;
			if (edge == -1) break;
			cin >> cost;
			v[vertex].push_back({ edge,cost });
		}
	}
}
void init(){
	while (!q.empty()) q.pop();
	memset(check, 0, sizeof(check));
}

void bfs(int node) {
	q.push({ node,0 }); check[node] = true;
	while (!q.empty()) {
		xy now = q.front(); q.pop();
		if (now.dis > max_distance) {
			max_distance = now.dis;
			max_node = now.point;
		}
		for (int i = 0; i < v[now.point].size(); i++) {
			xy next = v[now.point][i];
			if (check[next.point] == false) {
				next.dis = now.dis + next.dis;
				q.push(next); check[next.point] = true;
			}
		}
	}
}
int main() {
	input();

	bfs(1);
	init();
	bfs(max_node);

	cout << max_distance;
}
```

![1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%203.png](1167_%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%8C%E1%85%B5%E1%84%85%E1%85%B3%E1%86%B7%2097daa320457c4c5e97aaaea501a8bba5/Untitled%203.png)