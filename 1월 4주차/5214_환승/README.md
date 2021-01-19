# 5214_환승

BFS

# Pre

1. 유니온 파인드.
⇒ parent가 같은건 아니니까 bfs랑 똑같을 거 같다.
2. 하이퍼 튜브의 역마다 BFS.
⇒ 역 100,000개 * 하이퍼튜브 1,000개
3. ~~하이퍼 튜브를 unordered_set으로 관리.~~

![5214_%E1%84%92%E1%85%AA%E1%86%AB%E1%84%89%E1%85%B3%E1%86%BC%202e338270cd95478abcd028792f56e282/Untitled.png](5214_%E1%84%92%E1%85%AA%E1%86%AB%E1%84%89%E1%85%B3%E1%86%BC%202e338270cd95478abcd028792f56e282/Untitled.png)

# Error

1. **Index 문제**

    ```cpp
    vector <vector<int> > terminals;
    vector <vector<int> > hypertubes;

    for (int i = 0; i< M; i++) {
    	for (int j = 0; j < K; j++) {
    		int temp;
    		cin >> temp;
    		hyperterminals[i].push_back(temp);
    		terminals[temp].push_back(i);
    	}
    }
    ```

    - vector <vector<int> > allTerminals 에 이어붙이기
    - terminals :     0~N-1           까지  총 N 개
    - hypertubes : N~N+M-1     까지  총 M 개
2. 또, Index 문제

    헷갈림.

    - 입력은 1부터 N까지의 터미널
    - 내 Index는 0부터 N-1까지의 터미널

    ```cpp
    q.push({ 0, 1 });
    if (now.idx == N-1) {
    	cout << now.cnt;
    	exit(0);
    }
    ```

# Code

```cpp
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
```

![5214_%E1%84%92%E1%85%AA%E1%86%AB%E1%84%89%E1%85%B3%E1%86%BC%202e338270cd95478abcd028792f56e282/5214_.png](5214_%E1%84%92%E1%85%AA%E1%86%AB%E1%84%89%E1%85%B3%E1%86%BC%202e338270cd95478abcd028792f56e282/5214_.png)