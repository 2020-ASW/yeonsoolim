# Copy of 16637_괄호 추가하기 (잘못된 방법)

# 경우의 수  # 문자열 수식 계산

# Solve

1. **DFS를 통해 각각의 여러가지 경우의 수식을 구한다.**

    ```cpp
    void search(int curr, bitset <23> bit) {
    	if (curr == N+1) {
    		print(bit);
    		calc(bit); cout << '\n';
    		return;
    	}
    	for (int i = curr; i < N+2; i+=2) {
    		if (bit.test(i)) continue;
    		bit.set(i); bit.set(i + 2);
    		search(i, bit);
    		bit.reset(i); bit.reset(i + 2);
    	}
    }
    ```

2. **수식 ⇒ 괄호를 붙여놓은 수식  에 맞게 괄호 우선 계산.**

    ```cpp
    void gwalho(vector <string> &equation, bitset <23> bit) {
    	for (int i = 0; i < N; ) {
    		string C = "";
    		if (bit.test(i)) {
    			ll A = str[i] - '0';
    			ll B = str[i + 2] - '0';
    			
    			C = to_string(operateCalc(A, B, str[i + 1]));
    			i += 3;
    		}
    		else {
    			C += str[i++];
    		}
    		equation.push_back(C);
    	}
    }
    ```

3. **수식 ⇒ 괄호를 제거한 모든 값 계산.**

    ```cpp
    ll totalCalc(vector<string> &equation) {
    	ll A = stoi(equation[0]);
    	for (int i = 1; i < equation.size(); i += 2) {
    		ll B = stoi(equation[i + 1]);
    		string C = equation[i];
    		A = operateCalc(A, B, C[0]);
    	}
    	return A;
    }
    ```

# 잘못된 방법과 차이점.

- 직접 구현한 string to int는 음수에서 처리할 수 없었다.
    - 음수가 return 될 수 없었고,
    - 음수 +-x 음.양수 처리도 어려웠다.

# 주의점

1. **N 은 19 까지이지만, +2 까지를 봐야하고 2개를 한 셋트로 봐야했어서 23까지로 선언해주었다.**

    ```cpp
    bitset <23> bit;
    for (int i = curr; i < N + 2; i += 2) {
    	if (bit.test(i)) continue;
    	bit.set(i); bit.set(i + 2);
    	search(i, bit);
    	bit.reset(i); bit.reset(i + 2);
    }
    ```

2. **최댓값이 음수에서도 나올 수 있다.**

    ```cpp
    ll answer = -2147483648;
    ```

# Code

```cpp
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;
int N;
ll answer = -2147483648;
string str;
bitset <23> bit;
void input() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> str;
}

void print(bitset <23> bit) {
	cout << "\n";
	for (int i = 0; i < N; i++) {
		if (bit.test(i)) cout << str[i];
		else cout << "x";
	}cout << "\n";
}

string intToStr(int x) {
	string result = "";

	while (x > 0) {
		int end = x % 10;
		result += '0' + end;
		x /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}
ll strToInt(string x) {
	ll result = 0;
	while (x.size()) {
		result *= 10;
		result += x[0] - '0';
		x = x.substr(1, x.size());
	}
	return result;
}
ll operateCalc(ll A, ll B, char C) {
	ll result = 0;
	switch (C) {
	case '+':
		result = A + B;
		break;
	case '-':
		result = A - B;
		break;
	case '*':
		result = A * B;
		break;
	}
	return result;
}

void gwalho(vector <string> &equation, bitset <23> bit) {
	for (int i = 0; i < N; ) {
		string C = "";
		if (bit.test(i)) {
			ll A = str[i] - '0';
			ll B = str[i + 2] - '0';
			
			C = to_string(operateCalc(A, B, str[i + 1]));
			i += 3;
		}
		else {
			C += str[i++];
		}
		equation.push_back(C);
	}
}
ll totalCalc(vector<string> &equation) {
	ll A = stoi(equation[0]);
	for (int i = 1; i < equation.size(); i += 2) {
		ll B = stoi(equation[i + 1]);
		string C = equation[i];
		A = operateCalc(A, B, C[0]);
	}
	return A;
}
void calc(bitset <23> bit) {
	vector <string> equation;
	gwalho(equation, bit);
	
	if (equation.size() == 1) answer = (answer < stoi(equation[0]) ? stoi(equation[0]) : answer);
	ll A = totalCalc(equation);
	answer = (answer < A ? A : answer);
}
void search(int curr, bitset <23> bit) {

	if (curr == N + 1) {
		calc(bit);
		return;
	}
	for (int i = curr; i < N + 2; i += 2) {
		if (bit.test(i)) continue;
		bit.set(i); bit.set(i + 2);
		search(i, bit);
		bit.reset(i); bit.reset(i + 2);
	}
}

int main() {
	input();
	search(0, bit);
	cout << answer;
}
```

![Copy%20of%2016637_%E1%84%80%E1%85%AA%E1%86%AF%E1%84%92%E1%85%A9%20%E1%84%8E%E1%85%AE%E1%84%80%E1%85%A1%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20(%E1%84%8C%E1%85%A1%E1%86%AF%E1%84%86%E1%85%A9%E1%86%BA%E1%84%83%E1%85%AC%E1%86%AB%20%E1%84%87%E1%85%A1%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B8)%2072da176031d54ae6b57baf0c740d78e1/PNG__8.png](Copy%20of%2016637_%E1%84%80%E1%85%AA%E1%86%AF%E1%84%92%E1%85%A9%20%E1%84%8E%E1%85%AE%E1%84%80%E1%85%A1%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20(%E1%84%8C%E1%85%A1%E1%86%AF%E1%84%86%E1%85%A9%E1%86%BA%E1%84%83%E1%85%AC%E1%86%AB%20%E1%84%87%E1%85%A1%E1%86%BC%E1%84%87%E1%85%A5%E1%86%B8)%2072da176031d54ae6b57baf0c740d78e1/PNG__8.png)