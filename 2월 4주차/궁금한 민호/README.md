# 1507_궁금한 민호

Floyd-Warshall  

# Problem

강호는 N개의 도시로 이루어진 나라에 살고 있다. 각 도시는 M개의 도로로 연결되어 있으며, 각 도로를 지날 때 필요한 시간이 존재한다. 도로는 잘 연결되어 있기 때문에, 도시 A에서 B로 이동할 수 없는 경우는 존재하지 않는다.

도시 A에서 도시 B로 바로 갈 수 있는 도로가 있거나, 다른 도시를 거쳐서 갈 수 있을 때, 도시 A에서 B를 갈 수 있다고 한다.

강호는 모든 쌍의 도시에 대해서 최소 이동 시간을 구해놓았다. 민호는 이 표를 보고 원래 도로가 몇 개 있는지를 구해보려고 한다.

예를 들어, 예제의 경우에 모든 도시 사이에 강호가 구한 값을 가지는 도로가 존재한다고 해도 된다. 하지만, 이 도로의 개수는 최솟값이 아니다. 예를 들어, 도시 1-2, 2-3, 1-4, 3-4, 4-5, 3-5를 연결하는 도로만 있다고 가정해도, 강호가 구한 모든 쌍의 최솟값을 구할 수 있다. 이 경우 도로의 개수는 6개이고, 모든 도로의 시간의 합은 55이다.

모든 쌍의 도시 사이의 최소 이동 시간이 주어졌을 때, 이 나라에 존재할 수 있는 도로의 개수의 최솟값과 그 때, 모든 도로의 시간의 합을 구하는 프로그램을 작성하시오.

# Solve

- Floyd-Warshall의 특성을 이용한다.

    **모든 경로를 돌면서 꼭 필요한 도로만 남긴다.**

Floyd-Warshall에서 k, i, j 가 있을 때 표현 할 수 있는 것은 : i → j 까지 가는데 k 를 경유해 가는 비용이다.

민호가 구해놓은 표는 i → j 로 가는 직행 도로.
플로이드 와샬로 구할 수 있는 것은 i → k → j 로 가는 경유 도로.
1. (단, k가 i거나, j라면 직행 도로이므로, 빼주어야 한다. `if(k==i || k==j)  continue;`

2. 직행 도로와 비용이 같은 경유 도로가 있다면?

→ 직행 도로는 필요가 없다. 다른 도로로 대체 하여 더 좋은 비용을 이용할 수 있다.

`if(roads[i][k] + roads[k][j] == roads[i][j])  notNeed[i][j] = true;`

3. 직행 도로가 경유 도로보다 빠르다면? 

Floyd-Warshall 내부에서는  k==i, k==j 인 경우를 빼고 보고 있는데, 모순 적인 상황이 나온 것 이다.

`if(roads[i][k] + roads[k][j] < roads[i][j])  return -1;`

```cpp
for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(k==i || k==j) continue;
            if(roads[i][k] + roads[k][j] < roads[i][j]) return -1;
            if(roads[i][k] + roads[k][j] == roads[i][j]) {
                notNeed[i][j] = true;
            }
        }
    }
}
```

- 필요 없는 직행경로를 다 빼준다. 한 쌍씩 있으므로, /2도 해주어야 한다.

```cpp
for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(!notNeed[i][j]) result += roads[i][j];
        }
    }
    return (int)result/2;
}
```

# Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 100000

using namespace std;
vector <vector<int>> roads;
int N;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; roads.resize(N+1); for(auto &road : roads) road.resize(N+1);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> roads[i][j];
        }
    }
}
int floyd_warshall(){
    int result = 0;
    int result1= 0;
    vector<vector<bool>> notNeed;
    notNeed.resize(N+1); for(auto &tmp : notNeed) tmp.resize(N+1);

    for(int k=1; k<=N; k++){
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(k==i || k==j) continue;
                if(roads[i][k] + roads[k][j] < roads[i][j]) return -1;
                if(roads[i][k] + roads[k][j] == roads[i][j]) {
                    notNeed[i][j] = true;
                }
            }
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(!notNeed[i][j]) result += roads[i][j];
        }
    }
    return (int)result/2;
}
int main(){
    input();
    cout << floyd_warshall();
}
```

![1507_%E1%84%80%E1%85%AE%E1%86%BC%E1%84%80%E1%85%B3%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%86%E1%85%B5%E1%86%AB%E1%84%92%E1%85%A9%204131f0ea16bc4d1bb1eddb57564aba12/Untitled.png](1507_%E1%84%80%E1%85%AE%E1%86%BC%E1%84%80%E1%85%B3%E1%86%B7%E1%84%92%E1%85%A1%E1%86%AB%20%E1%84%86%E1%85%B5%E1%86%AB%E1%84%92%E1%85%A9%204131f0ea16bc4d1bb1eddb57564aba12/Untitled.png)