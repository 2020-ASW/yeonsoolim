#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <queue>

using namespace std;
struct cmp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
vector <vector <pair<int, int> > > edges;
priority_queue <pair<int, int>, vector<pair<int, int> >, cmp> pq;
int totalNode, totalWeight;
bitset <100> visit;

void setEdges(vector<vector<int>> costs) {
    edges.resize(totalNode);
    for (auto& cost : costs) {
        edges[cost[0]].push_back({ cost[1],cost[2] });
        edges[cost[1]].push_back({ cost[0],cost[2] });
    }
}
void prim() {
    int now = 0; visit.set(0);
    while (visit.count() != totalNode) {
        for (auto& edge : edges[now]) {
            if (visit.test(edge.first)) continue;
            pq.push({ edge.first,edge.second });
        }
        while (!pq.empty()) {
            pair<int, int> next = pq.top(); pq.pop();
            if (visit.test(next.first)) continue;
            visit.set(next.first);
            totalWeight += next.second;
            now = next.first;
            break;
        }
    }
}
int solution(int n, vector<vector<int>> costs) {
    totalNode = n;
    setEdges(costs);
    prim();
    return totalWeight;
}