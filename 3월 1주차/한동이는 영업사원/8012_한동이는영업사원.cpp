#include <iostream>
#include <algorithm>
#include <vector>
#define MAXEXP 15

using namespace std;
vector <vector<int>> graphs;
vector <vector<int>> ancestor;
vector <int> depth;
int N, M, start, dest;


void searchAncestor(int curr, int parent) {
    depth[curr] = depth[parent] + 1;
    ancestor[curr][0] = parent;
    for (int i = 1; i <= MAXEXP; i++) {
        int _next = ancestor[curr][i - 1];
        ancestor[curr][i] = ancestor[_next][i - 1];
    }

    for (auto& next : graphs[curr]) {
        if (next != parent) {
            searchAncestor(next, curr);
        }
    }
}

void initAncestor() {
    // 30,000 => 15
    ancestor.resize(N + 1); for (auto& _ : ancestor) _.resize(MAXEXP + 1);
    depth.resize(N + 1);
    searchAncestor(1, 0);

}

void setEqualDepth(int& left, int& right, int& length) {
    if (depth[left] < depth[right]) swap(left, right);
    while (depth[left] != depth[right]) {
        left = ancestor[left][0];
    }
}

void getCommonAncestor(int& left, int& right, int& length) {
    int LCA = left;
    if (left != right) {
        for (int jump = MAXEXP; jump >= 0; jump--) {
            if (ancestor[left][jump] != ancestor[right][jump]) {
                left = ancestor[left][jump];
                right = ancestor[right][jump];
            }
            LCA = ancestor[left][jump];
        }
    }
    length -= (depth[LCA] - 1) * 2;
}

void input() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; graphs.resize(N + 1);
    for (int i = 0; i < N-1; i++) {
        cin >> start >> dest;
        graphs[start].push_back(dest);
        graphs[dest].push_back(start);
    }

    initAncestor();

    cin >> M;
    cin >> start;
    int answer = 0;
    for (int i = 0; i < M-1; i++) {
        cin >> dest;
        int left = start, right = dest, length = depth[left] + depth[right] - 2;
        setEqualDepth(left, right, length);
        getCommonAncestor(left, right, length);
        answer += length;
        start = dest;
    }
    cout << answer;
}

int main() {
    input();
}