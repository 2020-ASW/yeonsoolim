# 17071_숨바꼭질5

#

# Pre

- 동생의 동선은 정해져 있다.

    ```cpp
    void getTimeSchedule() {
    	for (int s = 1; s <= 999; s++) {
    		if (K + s > 500000) break;
    		K = K + s;
    		maxSecond = s;
    		map.insert({ K,s });
    	}
    }
    ```

- 수빈의 동선은 3가지가 있다.

    ```cpp
    pair<int, int> nextA = { now.first - 1, now.second + 1 };
    pair<int, int> nextB = { now.first + 1, now.second + 1 };
    pair<int, int> nextC = { now.first * 2, now.second + 1 };

    if (inner(nextA)) {
    	if (visit[nextA.second].find(nextA.first) == visit[nextA.second].end()) {
    		q.push(nextA);
    		visit[nextA.second].insert(nextA.first);
    	}
    }
    if (inner(nextB)){
    	if (visit[nextB.second].find(nextB.first) == visit[nextB.second].end()) {
    		q.push(nextB);
    		visit[nextB.second].insert(nextB.first);
    	}
    }
    if (inner(nextC)) {
    	if (visit[nextC.second].find(nextC.first) == visit[nextC.second].end()) {
    		q.push(nextC);
    		visit[nextC.second].insert(nextC.first);
    	}
    }
    ```

- 두 인물이 만난다면 그 때의 시간이 정답.

    ```cpp
    while (!q.empty()) {
    	... ...
    	if (map.find(now.first) != map.end()) {
    		if (map[now.first] == now.second) {
    			answer = now.second;
    			break;
    		}
    	}
    	... ...
    }
    ```

# Fail

- **메모리 초과 (2차원 배열 500,000 * 999)**

    시간 최대 999 second
    위치 최대 500,000

    위 모두를 체크하기 위해서는 500000 , 999 의 visit 이 필요하다.

- **메모리 초과 (배열 500,000 + set)**

    ⇒ 2차원 배열을 1차원 + set으로 바꿨으나, 같이 메모리 초과.

# Solve

수빈의 발자취를 중복 체크 하기 위해서는 visit 체크가 필수.

- **방문을 했냐 안했냐 + 했다면 짝수 시간에 ? / 홀수 시간에 ? 로 판별 가능**

    2차원 배열 500,000 * 2 개로만 체크 가능하다.

- **Time 별 동생의 발자취를 옮길 때, 수빈이 왔다 간적이 있는지를 확인한다. (수빈의 동선이 더 자유로우므로)**

    ```cpp
    if (older == younger || visit[younger][s % 2]) { //언니가 많이 움직였고 움직였던 장소.
    	cout << s;
    	exit(0);
    }
    ```

- **수빈의 발자취도 마찬가지로 짝수 시간 / 홀수 시간 구별해서 체크를 해준다.**

    ```cpp
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
    ```

- **예외 처리**
    1. N == K 일 때, 즉 0초만에 만나있다.

        ```cpp
        if (N == K) {
        	cout << "0";
        	exit(0);
        }
        ```

    2. 동생의 동선이 500,000을 넘었다.

        ```cpp
        if (younger + s > 500000) {
        	cout << "-1";
        	exit(0);
        }
        ```

# Code

```cpp
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
```

![17071_%E1%84%89%E1%85%AE%E1%86%B7%E1%84%87%E1%85%A1%E1%84%81%E1%85%A9%E1%86%A8%E1%84%8C%E1%85%B5%E1%86%AF5%20f679325e318d4521a82b4d125e2cae24/PNG__7.png](17071_%E1%84%89%E1%85%AE%E1%86%B7%E1%84%87%E1%85%A1%E1%84%81%E1%85%A9%E1%86%A8%E1%84%8C%E1%85%B5%E1%86%AF5%20f679325e318d4521a82b4d125e2cae24/PNG__7.png)