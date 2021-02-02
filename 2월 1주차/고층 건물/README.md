# 1027_고층 건물

# dp #에라토스테네스의 체 응용

![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled.png)

# Pre

1. **DP를 이용해 변화를 구해야 하나?**

    ![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%201.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%201.png)

2. **정렬을 해서 돌면 되나?**

    ![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%202.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%202.png)

⇒ 예시 정답이 7인것으로 보아 육안으로는 확인이 불가능하다.

![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%203.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%203.png)

# 기울기 :

$tan(h) = (y-y1)/(x-x1)$

# Solve

가운데를 기준으로 봤을 때 : buildings[i]

**left는 building이 커진다면 기울기가 감소한다.**

```cpp
double minGradient = 2147483647;
while(i - cnt >= 0) {
	double gradient = (double)(buildings[i] - buildings[i - cnt]) / cnt;
	if (minGradient > gradient) {
		minGradient = gradient;
		leftCnt++;
	}
}
```

**right는 building이 커진다면 기울기가 증가한다.**

```cpp
double maxGradient = -2147483647;
while (i + cnt < N) {
	double gradient = (double)(buildings[i+cnt] - buildings[i]) / cnt;
	if (maxGradient < gradient) {
		maxGradient = gradient;
		rightCnt++;
	}
}
```

![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%204.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%204.png)

# Error

기울기가 너무 헷갈려서 이것저것 다 해보았다...

left, right끝까지 모두 봐주어야 한다. 기울기에 따라서 안보일 것 같은것도 보일 수 있다.

# code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, answer;
vector <int> buildings;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		int building;
		cin >> building;
		buildings.push_back(building);
	}
}
int main() {
	input();

	for (int i = 0; i < buildings.size(); i++) {
		int cnt = 1, leftCnt = 0;
		double minGradient = 2147483647;
		while(i - cnt >= 0) {
			double gradient = (double)(buildings[i] - buildings[i - cnt]) / cnt;
			if (minGradient > gradient) {
				minGradient = gradient;
				leftCnt++;
			}
			cnt++;
		}
		int rightCnt = 0; cnt = 1;
		double maxGradient = -2147483647;
		while (i + cnt < N) {
			double gradient = (double)(buildings[i+cnt] - buildings[i]) / cnt;
			if (maxGradient < gradient) {
				maxGradient = gradient;
				rightCnt++;
			}
			cnt++;
		}
		answer = (answer < (leftCnt + rightCnt) ? (leftCnt + rightCnt) : answer);
	}
	cout << answer;
}
```

![1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%205.png](1027_%E1%84%80%E1%85%A9%E1%84%8E%E1%85%B3%E1%86%BC%20%E1%84%80%E1%85%A5%E1%86%AB%E1%84%86%E1%85%AE%E1%86%AF%20e74209e04a7743169b9e0a6d6cd78360/Untitled%205.png)