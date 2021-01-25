//#include <iostream>
//#include <vector>
//#include <bitset>
//#include <algorithm>
//
//using namespace std;
//int V, endNode, maxLength;
//vector <vector<pair<int, int> > > nodes;
//void input() {
//	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
//	cin >> V;
//	nodes.resize(V+1);
//	for (int i = 0; i < V; i++) {
//		int vertex, edge, cost;
//		cin >> vertex;
//		while (1) {
//			cin >> edge;
//			if (edge == -1) break;
//			cin >> cost;
//			nodes[vertex].push_back({ edge,cost });
//		}
//	}
//}
//
//void dfsEndNode(int now, int length, bitset <100001> visit) {
//	
//	if (length > maxLength) {
//		maxLength = length;
//		endNode = now;
//	}
//	
//	for (auto& next : nodes[now]) {
//		if (visit.test(next.first)) continue;
//		visit.set(next.first);
//		dfsEndNode(next.first, length+next.second, visit.set(next.first));
//		visit.reset(next.first);
//	}
//}
//
//void getEndNode(int node) {
//	maxLength = 0;
//	bitset <100001> visit; visit.reset(); visit.set(node);
//	dfsEndNode(node, 0, visit);
//}
//
//int main() {
//	input();
//	getEndNode(1);
//	getEndNode(endNode);
//	cout << maxLength;
//}

#include <iostream>
#include < vector>
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
	cout << max_node << "\n";
	bfs(max_node);

	cout << max_distance;
}