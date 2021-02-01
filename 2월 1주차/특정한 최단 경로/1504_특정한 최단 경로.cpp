#include <iostream>
#include <vector>
#include <algorithm>
#define INF 2147483647
#define ll long long

using namespace std;
int N, E, a, b, c, v1, v2;
vector <vector <ll> > graph;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> E;
	graph.resize(N + 1); for (int i = 1; i <= N; i++) graph[i].resize(N + 1);
	fill(graph.begin(), graph.end(), vector<ll>(N+1, INF));
	for (int i = 1; i <= N; i++) graph[i][i] = 0;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		graph[a][b] = min(graph[a][b], (ll)c);
		graph[b][a] = min(graph[b][a], (ll)c);
	}
	cin >> v1 >> v2;
}

void floydWarshall() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
}
ll classfication() {
	ll v1Dist = graph[1][v1] + graph[v1][v2] + graph[v2][N];
	ll v2Dist = graph[1][v2] + graph[v2][v1] + graph[v1][N];
	ll answer = min(v1Dist, v2Dist);

	return (answer >= INF ? -1 : answer);
}
int main() {
	input();

	floydWarshall();

	cout << classfication();
}