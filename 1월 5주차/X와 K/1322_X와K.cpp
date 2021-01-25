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