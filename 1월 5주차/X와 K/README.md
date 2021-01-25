# 1322_X와 K

# 문제 이해

- X, K 는 20,000,000,000 (20억)이다.
- X+Y = X | Y 인 Y중 K 번째 작은 Y를 구해야 한다.
- X, Y는 자연수.

# Pre

냅다 그냥 돌려버리기. ⇒ 시간초과  20억이기 때문

# 규칙 찾기.

X가 5일 때, K를 바꿔보고 만족하는 Y를 찾는다.

**X : 5  K : 1**

0101   + ⇒ 6
0001    |  ⇒ 5

**X : 5  K : 2**

**0101   + ⇒ 7
0010    |  ⇒ 7**

**X : 5  K : 3**

0101   + ⇒ 8
0011    |  ⇒ 7

**X : 5  K : 4**

0101   + ⇒ 9
0100    |  ⇒ 5

**X : 5  K : 5**

0101   + ⇒ 10
0101    |  ⇒ 5

**X : 5  K : 6**

0101   + ⇒ 11
0110    |  ⇒ 7

**X : 5  K : 7**

0101   + ⇒ 12
0111    |  ⇒ 7

**X : 5  K : 8**

**0101   + ⇒ 13
1000    |  ⇒ 13**

**X : 5  K : 9**

0101   + ⇒ 14
1001    |  ⇒ 13

**X : 5  K : 10**

**0101   + ⇒ 15
1010    |  ⇒ 15**

 

- 추측
Y :

        0010
        1000
        1010
         ...
       10000   //그 다음.

**⇒ 규칙.**

![1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/Untitled.png](1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/Untitled.png)

- **무조건 X의 켜진 bit는 Y에서는 꺼져있다.**

# K 번째???

![1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/Untitled%201.png](1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/Untitled%201.png)

- X의 켜진 bit를 제외하고 보면,  1, 2, 3, 4, 5, 6 씩 늘어나고, 고정된 X와 합쳐지는 것을 볼 수 있다.

# Solve

1. K번째 자릿수에 매칭되는 틀을 만들어 놓는다.
2. X에 의해 고정되는 bit를 구해놓는다.
    - digitK [ ]  자릿수를 알아내기 위한 배열
    - fixX []      0으로 고정되야 하는 비트

    ```cpp
    for (uint i = 0; i<32; i++) {
    	if (K & (1 << i)) digitK[i] = 1;
    	else digitK[i] = 0;
    	if (X & (1 << i)) fixX[i] = 0;
    }
    ```

3. 구해놓은 K와 X를 이용해 32 ~ 64bit사이 answer를 구한다.
    - fixX가 0이라면 고정해야하므로 0을 넣어주고,
    - fixX가 0이아니면 digitK에 해당하는 값을 넣어준다.

    ```cpp
    for (int i = 0, k = 0; k < 32; i++) {
    	if (i < 32 && fixX[i] == 0) answer[i] = 0;
    	else answer[i] = digitK[k++];
    }
    ```

4. answer 배열을 이용해 값으로 바꿔준다.

    ```cpp
    for (ull i = 0; i < 64; i++) {
    	if (answer[i] == 1) Y |= (1ULL << i);
    }
    cout << Y;
    ```

# Code

```cpp
#include <iostream>
#include <string>
#include <cstring>
#define uint unsigned int
#define ll long long
#define ull unsigned long long
using namespace std;
uint X, K, cnt;
void input() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> X >> K;
}

void solve() {
	ll answer[64];
	ull Y = 0;
	int digitK[32];
	int fixX[32];
	memset(answer, 0, sizeof(answer));
	memset(fixX, -1, sizeof(fixX));
	for (uint i = 0; i<32; i++) {
		if (K & (1 << i)) digitK[i] = 1;
		else digitK[i] = 0;
		if (X & (1 << i)) fixX[i] = 0;
	}
	
	for (int i = 0, k = 0; k < 32; i++) {
		if (i < 32 && fixX[i] == 0) answer[i] = 0;
		else answer[i] = digitK[k++];

	}
	
	for (ull i = 0; i < 64; i++) {
		if (answer[i] == 1) Y |= (1ULL << i);
	}
	cout << Y;
}

int main() {
	input();
	solve();
}
```

![1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/PNG__6.png](1322_X%E1%84%8B%E1%85%AA%20K%20f93b8a6e6cac41d4b857a84b5eaaaba6/PNG__6.png)