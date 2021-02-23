#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
vector <vector<int> > sumTree;
int answer = 0;
bool inner(int depth, int idx){
    return (0<=idx && idx<=depth);
}

void setSumTree(vector<vector<int>> &triangle){
    sumTree.resize(triangle.size());
    for(int i=0; i<triangle.size(); i++)
        sumTree[i].resize(triangle[i].size());
    sumTree[0][0] = triangle[0][0];
}

void bfs(vector<vector<int>> &triangle){
    int depth = 0;

    for(int currDepth = 0; currDepth<=triangle.size()-2; currDepth++){
        for(int next = 0; next<triangle[currDepth+1].size(); next++){
            int nextValue = triangle[currDepth+1][next];
            if(next == 0)
                sumTree[currDepth+1][0] = sumTree[currDepth][0] + nextValue;
            else if(next == triangle[currDepth+1].size()-1)
                sumTree[currDepth+1][next] = sumTree[currDepth][next-1] + nextValue;
            else{
                int leftParentIdx = next-1;
                int rightParentIdx = next;
                sumTree[currDepth+1][next] = max(sumTree[currDepth+1][next], sumTree[currDepth][leftParentIdx] + nextValue);
                sumTree[currDepth+1][next] = max(sumTree[currDepth+1][next], sumTree[currDepth][rightParentIdx] + nextValue);
            }
            answer = max(answer, sumTree[currDepth+1][next]);
        }
    }
}

int solution(vector<vector<int>> triangle) {
    setSumTree(triangle);
    bfs(triangle);
    return answer;
}