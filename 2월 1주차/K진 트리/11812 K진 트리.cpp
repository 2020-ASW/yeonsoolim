#include <iostream>
#define ll long long
using namespace std;
ll N, K, Q, x, y;
ll distance() {
	ll aCnt = 0, bCnt = 0, a = x, b = y;
	while(a != b) {
		while (a > b) {
			aCnt++;
			a = (a + K - 2) / K;
		}
		while (a < b) {
			bCnt++;
			b = (b + K - 2) / K;
		}
	}
	return aCnt+bCnt;
}

void input() {
	cin >> N >> K >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> x >> y;
		if (K == 1) cout << abs(x - y) << '\n';
		else cout << distance() << '\n';
	}
}
int main() {
	input();
}