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