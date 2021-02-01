# 1504 특정한 최단 경로

Floyd-Warshall  

# Pre

1. 방향성이 없다 :  a→b b → a를 고려해주자.
2. 1 → N 까지 간다.
3. v1, v2를 경유해가는데,
max(1 → v1 → v2 → N  ,  1 → v2 → v1 → N ) 이 아닐까?
확실히 두 개의 길이는 다를 것.

# Solve

1. **자기 자신 : 0  &  경로가 없는 곳은 INF로 초기화 한다.**

    ```cpp
    graph.resize(N + 1); for (int i = 1; i <= N; i++) graph[i].resize(N + 1);
    fill(graph.begin(), graph.end(), vector<ll>(N+1, INF));
    for (int i = 1; i <= N; i++) graph[i][i] = 0;
    ```

2. **Floyd-Warshall을 이용해 모든 정점에 대한 모든 최단 경로를 구해준다.**

    ```cpp
    void floydWarshall() {
    	for (int k = 1; k <= N; k++) {
    		for (int i = 1; i <= N; i++) {
    			for (int j = 1; j <= N; j++) {
    				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
    			}
    		}
    	}
    }
    ```

3. **max(1 → v1 → v2 → N  ,  1 → v2 → v1 → N )** 

    ```cpp
    ll classfication() {
    	ll v1Dist = graph[1][v1] + graph[v1][v2] + graph[v2][N];
    	ll v2Dist = graph[1][v2] + graph[v2][v1] + graph[v1][N];
    	ll answer = min(v1Dist, v2Dist);

    	return (answer >= INF ? -1 : answer);
    }
    ```

# Error

INF 를 INTMAX값 2147483647로 지정했는데,  경로를 더하는 과정에서 오버플로우가 날 수 있다.

⇒ `vector <vector <ll> > graph;`  // long long으로 vector를 구성.

![1504%20%E1%84%90%E1%85%B3%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%8E%E1%85%AC%E1%84%83%E1%85%A1%E1%86%AB%20%E1%84%80%E1%85%A7%E1%86%BC%E1%84%85%E1%85%A9%20726bf6d108dd4baa8b9785521afa801e/Untitled.png](1504%20%E1%84%90%E1%85%B3%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%8E%E1%85%AC%E1%84%83%E1%85%A1%E1%86%AB%20%E1%84%80%E1%85%A7%E1%86%BC%E1%84%85%E1%85%A9%20726bf6d108dd4baa8b9785521afa801e/Untitled.png)