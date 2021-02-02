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