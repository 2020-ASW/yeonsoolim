# 1135 뉴스 전하기

# Problem

- 민식이 (0) 기준 Tree 구조.
- 1번에 1-child 씩 1-time이 걸린다.
- 모든 Node에 걸리는 최소 시간을 구한다.
- i번 째 입력이 parent의 idx가 들어오므로 tree를 구성해주어야 한다.

# Init

- i번 째 입력이 parent의 idx가 들어오므로 tree를 구성해주어야 한다.
    - 한 Node의 기본 소요 시간은 child의 수.  `times[temp] += 1;`
    - 입력 값은 한 Node의 부모 index → 부모 벡터에 자식을 추가해준다. :`trees[temp].push_back(i);`

    ```cpp
    int N;
    vector <vector<int>> trees;
    vector <int> times;

    for(int i=0; i<N; i++){
        cin >> temp;
        if(temp == -1) continue;
        times[temp] += 1;
        trees[temp].push_back(i); // Child Node Add
    }
    ```

# Pre

- 한 Node의 소요 시간은
    1. Child 수   or
    2. Child의 큰 수 + 그 수의 count
    → times[child] 가 큰 수를 1초에 전화 할 것이고, 같다면 2~~~초로 갈 것이다.

        ```cpp
            int maximumTime = 0;
            int maximumCnt = 1;
            for(auto &child : trees[curr]){
                int tempTime = propagation(child);

                if(maximumTime == tempTime) maximumCnt++;
                else if(maximumTime < tempTime){
                    maximumCnt = 1; maximumTime = tempTime;
                }
            }

            if(maximumTime == 0) times[curr] = times[curr];
            else times[curr] = max(times[curr], maximumTime + maximumCnt);

            return times[curr];
        ```

# Error

![1135%20%E1%84%82%E1%85%B2%E1%84%89%E1%85%B3%20%E1%84%8C%E1%85%A5%E1%86%AB%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20fe49276e12784d299259737e71b49fdb/Untitled.png](1135%20%E1%84%82%E1%85%B2%E1%84%89%E1%85%B3%20%E1%84%8C%E1%85%A5%E1%86%AB%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20fe49276e12784d299259737e71b49fdb/Untitled.png)

> 19
-1 0 0 0 0
1 1 1 2 2 2 3 3 3 4 4 4 4 4

일 때, 5가 크지만, 4초에 3에게 보낸 전화가 기준이 될 것.

# Solve

- 한 Node의 Child의 소요 시간을 추출해서 시간 마다 뿌려본다.
    - child의 시간을 모은 vector를 정렬 후.
    - 1초 ~ child.size()초 까지 기준 점을 (max) 찾는다.

    ```cpp
    vector<int> childTimes;
    for(auto &child : trees[curr]){
        int tempTime = propagation(child);
        childTimes.push_back(tempTime);
    }

    sort(childTimes.begin(), childTimes.end());

    int callTime = childTimes.size();
    for(auto &childTime : childTimes){
        times[curr] = max(times[curr], childTime+callTime--);
    }

    return times[curr];
    ```

# Code

```jsx
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector <vector<int>> trees;
vector <int> times;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; trees.resize(N); times.resize(N);
    int temp;
    for(int i=0; i<N; i++){
        cin >> temp;
        if(temp == -1) continue;
        times[temp] += 1;
        trees[temp].push_back(i); // Child Node Add
    }
}
void treePrint(){
    for(int i=0 ;i<times.size(); i++){
        cout << i<< " : "<<times[i]<<'\n';
    }cout <<'\n';
}
int propagation(int curr){
    if(times[curr] == 0){
        // leaf Node
        return 0;
    }
    vector<int> childTimes;
    for(auto &child : trees[curr]){
        int tempTime = propagation(child);
        childTimes.push_back(tempTime);
    }
    
    sort(childTimes.begin(), childTimes.end());
    
    int callTime = childTimes.size();
    for(auto &childTime : childTimes){
        times[curr] = max(times[curr], childTime+callTime--);
    }

    return times[curr];
}

int main(){
    input();
    propagation(0);
    //treePrint();
    cout << times[0];
}
```

![1135%20%E1%84%82%E1%85%B2%E1%84%89%E1%85%B3%20%E1%84%8C%E1%85%A5%E1%86%AB%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20fe49276e12784d299259737e71b49fdb/Untitled%201.png](1135%20%E1%84%82%E1%85%B2%E1%84%89%E1%85%B3%20%E1%84%8C%E1%85%A5%E1%86%AB%E1%84%92%E1%85%A1%E1%84%80%E1%85%B5%20fe49276e12784d299259737e71b49fdb/Untitled%201.png)