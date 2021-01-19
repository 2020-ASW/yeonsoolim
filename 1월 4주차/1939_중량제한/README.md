# 1939_중량제한

#Binary Search  #DFS  #BFS

# Pre

1. ~~섬이 1만개다. 완전 탐색하면 10000*10000 = 100,000,000 (1억)~~
2. 돌고 있는 minWeight 보다 작으면 못가니까 return;
3. startCity → endCity 에 도달했을 때, minWeight 가 가장 큰 값.

# Error

1. startCity → endCity 까지 1번에 도달하는게 아니라, 
10만 개의 query만큼 거쳐 갈 수 있다.
⇒ 메모리 초과
2. bitset  vs  bool Array
**bitset으로 10001개 체크를 하면 시간초과.
bool Array로 10001개 체크를 하면 통과.**

    대체적으로 bitset이 빠르다.

    ![1939_%E1%84%8C%E1%85%AE%E1%86%BC%E1%84%85%E1%85%A3%E1%86%BC%E1%84%8C%E1%85%A6%E1%84%92%E1%85%A1%E1%86%AB%20e17898003580466aa25619165a126c4a/Untitled.png](1939_%E1%84%8C%E1%85%AE%E1%86%BC%E1%84%85%E1%85%A3%E1%86%BC%E1%84%8C%E1%85%A6%E1%84%92%E1%85%A1%E1%86%AB%20e17898003580466aa25619165a126c4a/Untitled.png)

    But, Compiler Version마다 상이하다.  백준 (gcc 10.2)
    **gcc 10.1 이상 부터 boolean Array가 더 빠르다.**

    [https://quick-bench.com/q/MezIvXR0CFE4ycE92fBxkeuk278](https://quick-bench.com/q/MezIvXR0CFE4ycE92fBxkeuk278)

# Solve

1. 구하려 것 : **옮길 수 있는** **중량의 최댓값**은 10억.
→ 10억 Binary Search ⇒ $O(log N)$ 
+  input : weight 중 maxWeight 는 10억 이하.

    ```cpp
    cin >> A >> B >> weight;
    maxWeight = (maxWeight < weight ? weight : maxWeight);

    void binarySearch() {
    	int left = 1;
    	int right = maxWeight;

    	while (left <= right) {

    	}
    }
    ```

2. BS에서 mid 는 싣고 경로를 가볼 중량.
1 ~ 10억

    ```cpp
    int mid = (right - left) / 2 + left;
    search(startCity, mid);
    ```

3. DFS로 탐색 할 것 → startCity에서 mid중량을 싣고 endCity로 갈 수 있는가.

    ```cpp
    bool search(int curr, int mid) {
    	// 중요  방문 체크를 풀지 않는다.
    	**visit[curr] = true;**
    	if (curr == endCity) {
    		return true;
    	}

    	for (auto& city : cities[curr]) {
    		if (visit[city.first]) continue;  // 이미 체크
    		if (city.second < mid) continue;
    		if (search(city.first, mid)) return true;
    	}
    	return false;
    }
    ```

    - **visit[curr]에 대한 dfs를 돌고와서 visit[curr] = false;를 하지 않는다.**
    startCity → endCity를 가기만 하면되고 그 사이에 다른 경로는 중요치 않다.

### DFS와 BFS의 차이.

- DFS : 재귀를 돌리고 있으므로, 경로를 발견해도 해당하는 전체를 멈출 순 없다.
- BFS : while안에서 돌고 있을 때, 경로를 발견한다면 바로 멈출 수 있다.

# Code

```cpp
#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <cstring>
#define ll long long
#define uint unsigned int
#define INTMAX 2147483647

using namespace std;
int N, M, A, B, weight, startCity, endCity, answer, maxWeight;
vector <vector<pair<int, int> > > cities;
bool visit[10001];
void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	cities.resize(N + 1);
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> weight;
		maxWeight = (maxWeight < weight ? weight : maxWeight);
		cities[A].push_back({ B,weight });
		cities[B].push_back({ A,weight });
	}
	cin >> startCity >> endCity;
}

bool search(int curr, int mid) {
	visit[curr] = true;
	if (curr == endCity) {
		return true;
	}

	for (auto& city : cities[curr]) {
		if (visit[city.first]) continue;  // 이미 체크
		if (city.second < mid) continue;
		if (search(city.first, mid)) return true;
	}
	return false;
}

void binarySearch() {
	int left = 1;
	int right = maxWeight;

	while (left <= right) {
		int mid = (right - left) / 2 + left;
		memset(visit, false, sizeof(visit));
		bool res = search(startCity, mid);
		if (res) {
			left = mid + 1;
			answer = mid;
		}
		else right = mid - 1;
	}
}
int main() {
	input();

	binarySearch();

	cout << answer;
}
```

![1939_%E1%84%8C%E1%85%AE%E1%86%BC%E1%84%85%E1%85%A3%E1%86%BC%E1%84%8C%E1%85%A6%E1%84%92%E1%85%A1%E1%86%AB%20e17898003580466aa25619165a126c4a/1939_.png](1939_%E1%84%8C%E1%85%AE%E1%86%BC%E1%84%85%E1%85%A3%E1%86%BC%E1%84%8C%E1%85%A6%E1%84%92%E1%85%A1%E1%86%AB%20e17898003580466aa25619165a126c4a/1939_.png)