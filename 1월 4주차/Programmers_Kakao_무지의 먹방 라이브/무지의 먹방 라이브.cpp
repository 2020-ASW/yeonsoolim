#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#define ll long long

using namespace std;
vector <pair<int, int> > histogram;
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}
bool cmp2(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}
bool outOfTotal(vector<int> food_times, long long k) {
    ll total = 0;
    for (int i = 0; i < food_times.size(); i++) total += food_times[i];
    if (total <= k) return true;
    return false;
}
void setHistogram(vector<int> food_times) {
    for (int i = 0; i < food_times.size(); i++) {
        histogram.push_back({ food_times[i],i + 1 });
    }
}
int solution(vector<int> food_times, long long k) {
    int N = food_times.size();
    ll K = k;
    if (outOfTotal(food_times, K)) return -1;
    setHistogram(food_times);

    ll minFood, minFoodCnt, acc = 0;
    sort(histogram.begin(), histogram.end(), cmp);
    int cnt = -1;
    while (1) {
        cnt++;
        minFood = histogram[cnt].first - acc;
        acc += minFood;

        if (minFood * N >= K) {
            sort(histogram.begin() + cnt, histogram.end(), cmp2);
            return histogram[cnt + (K % N)].second;
        }
        K -= (minFood * N);
        N -= 1;

    }
}