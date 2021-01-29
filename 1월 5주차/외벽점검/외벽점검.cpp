#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <stdlib.h>
#define uint unsigned int
using namespace std;
bool cmp(const int& a, const int& b) {
    return a > b;
}
int getNextDistance(bool reverse, int n, int w, vector<int>& weaksOrder) {
    int nextDistance = weaksOrder[w + 1] - weaksOrder[w];
    if (!reverse && weaksOrder[w] > weaksOrder[w + 1]) nextDistance += n;
    else if (reverse && weaksOrder[w] > weaksOrder[w + 1]) nextDistance = abs(nextDistance);
    else if (reverse && nextDistance > 0) nextDistance = n - nextDistance;
    return nextDistance;
}
bool calc(bool reverse, int n, vector<int> friends, vector<int>& weaksOrder) {
    int w = 0;
    unordered_set <int> set;

    for (int i = 0; i < friends.size(); i++) {
        int range = friends[i];
        int nextDistance;
        while (range > 0) {
            nextDistance = getNextDistance(reverse, n, w, weaksOrder);

            if (nextDistance <= range) {
                range -= nextDistance;
                set.insert(w);
                set.insert(w + 1);
                if (range > 0) w++;
                else w += 2;
            }
            else {
                set.insert(w);
                w++;
                break;
            }
            if (set.size() >= weaksOrder.size()) return true;
        }
        if (set.size() >= weaksOrder.size()) return true;

    }
    if (set.size() >= weaksOrder.size()) return true;
    else return false;
}


bool friendsOrder(int depth, vector <int> friends, int mid, int n, vector<int>& weak, vector<int>& dist, uint bit) {
    if (depth == mid) {
        for (int start = 0; start < weak.size(); start++) {
            vector <int> weaksOrder;
            for (int next = start; next < weak.size() + start; next++) {
                weaksOrder.push_back(weak[next % weak.size()]);
            }
            if (friends.size() >= weaksOrder.size()) return true;

            bool res = calc(false, n, friends, weaksOrder);
            if (res) return true;
            reverse(weaksOrder.begin(), weaksOrder.end());
            res = calc(true, n, friends, weaksOrder);
            if (res) return true;
        }
        return false;
    }
    bool res = false;
    for (int i = 0; i < mid; i++) {
        if (bit & (1 << i)) continue;
        friends[depth] = dist[i];
        res = friendsOrder(depth + 1, friends, mid, n, weak, dist, bit | (1 << i));
        if (res) return true;
    }
    return res;
}

bool support(int mid, int n, vector<int>& weak, vector<int>& dist) {

    uint bit = 0;
    vector<int> friends(mid);
    return friendsOrder(0, friends, mid, n, weak, dist, bit);
}

void binarySearch(int& answer, int n, vector<int>& weak, vector<int>& dist) {
    int left = 1, right = dist.size();
    while (left <= right) {
        int mid = (right - left) / 2 + left;
        if (support(mid, n, weak, dist)) {
            right = mid - 1;
            answer = (answer > mid ? mid : answer);
        }
        else {
            left = mid + 1;
        }
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    if (n <= 2) return 1;

    int answer = 2147483647;
    sort(dist.begin(), dist.end(), cmp);
    if (n <= dist[0]) return 1;
    binarySearch(answer, n, weak, dist);

    return (answer == 2147483647 ? -1 : answer);
}