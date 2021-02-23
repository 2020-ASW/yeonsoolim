# Programmers 정수 삼각형

# Problem

![Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled.png](Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled.png)

### 문제 설명

위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

### 제한사항

- 삼각형의 높이는 1 이상 500 이하입니다.
- 삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.

### 입출력 예

[[7], [3, 8], [8, 1, 0], [2, 7, 4, 4], [4, 5, 2, 6, 5]]       30

# Solve

- 마지막에 어떤 수가 나올지 모르므로, Greedy한 방법으론 풀 수 없다.
- DP를 이용하여 누적된 값을 저장한다.

    저장할 Tree

    ```cpp
    void setSumTree(vector<vector<int>> &triangle){
        sumTree.resize(triangle.size());
        for(int i=0; i<triangle.size(); i++)
            sumTree[i].resize(triangle[i].size());
        sumTree[0][0] = triangle[0][0];
    }
    ```

    ![Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled%201.png](Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled%201.png)

    - 현재 Node에서는 왼쪽 위에서 온 leftParent, 오른쪽 위에서 온 rightParent를 가질 수 있다.
    - 현재 Node가 양 끝쪽에 있다면 Parent가 1개 밖에 없다.

    DP 탐색

    ```cpp
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
    ```

# Code

```cpp
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
```

![Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled%202.png](Programmers%20%E1%84%8C%E1%85%A5%E1%86%BC%E1%84%89%E1%85%AE%20%E1%84%89%E1%85%A1%E1%86%B7%E1%84%80%E1%85%A1%E1%86%A8%E1%84%92%E1%85%A7%E1%86%BC%209a4452849c5348c19cbb3af27f769d40/Untitled%202.png)