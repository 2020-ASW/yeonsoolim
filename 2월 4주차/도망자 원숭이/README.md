# 1602_도망자 원숭이

Floyd-Warshall  

# Problem

원숭이가 사는 나라는 여러 개의 도시와 도시들을 연결하는 길들로 구성되어 있다. 각 길들은 두 개의 도시를 양방향으로 연결한다. 또한, 각 길은 지나갈 때마다 일정한 시간이 걸린다. 원숭이는 시작도시에서 탈출하여 도착도시까지 최대한 빠른 시간에 가야한다.

그런데 원숭이의 오랜 숙적 멍멍이가 이를 갈며 원숭이를 기다리고 있었다. 멍멍이는 원숭이가 도망가는 경로 중 시작점과 도착점을 포함한 도시 중 한 군데에서 원숭이를 괴롭히기로 계획했다. 각 도시마다 구조가 다르기 때문에 멍멍이가 원숭이를 괴롭힐 수 있는 시간이 정해져있다.

그래서 멍멍이는 원숭이가 도망가는 경로 상에 있는 모든 도시들 중에서 가장 오랜 시간동안 괴롭힐 수 있는 도시에서 괴롭히기로 계획했다. 원숭이는 멍멍이를 피할 수 없다. 피할 수 없다면 즐겨라! 시작도시와 도착도시가 주어졌을 때, 원숭이가 최대한 빨리 도망갈 수 있는 시간을 구하는 프로그램을 작성하시오.

[1602번: 도망자 원숭이](https://www.acmicpc.net/problem/1602)

# Solve

![1602_%E1%84%83%E1%85%A9%E1%84%86%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%A1%20%E1%84%8B%E1%85%AF%E1%86%AB%E1%84%89%E1%85%AE%E1%86%BC%E1%84%8B%E1%85%B5%20971c55ca20c24f5fb4769505bed36a99/Untitled.png](1602_%E1%84%83%E1%85%A9%E1%84%86%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%A1%20%E1%84%8B%E1%85%AF%E1%86%AB%E1%84%89%E1%85%AE%E1%86%BC%E1%84%8B%E1%85%B5%20971c55ca20c24f5fb4769505bed36a99/Untitled.png)

원숭이 는 최소 경로로 가야한다.

멍멍이 는 최대 값으로 가야한다.

- 기본 Floyd-Warshall 중 최단 경로를 구할 때
+ 그 경로에서 가장 큰 멍멍이의 Value가 고려 되어야 함.
- **동시성 필요.**

    원숭이의 경로에 따라 매번 멍멍이의 **최댓값**이 바뀔 수 있으므로 동시 필요.

원숭이는  [1, 5]를 갈 때 : 1 - 4 - 5 (35) 를 가고 싶어하고
멍멍이는   1 - 4 - 5 로 지나갈 때, 15 값을 가진다.  ⇒ 50

**원숭이가  [1, 5]를 갈 때 : 1 - 2 - 3 - 5 (40) 를 간다면
멍멍이는   1 - 2 - 3 - 5 로 지나갈 때, 5 값을 가진다. ⇒ 45**

1. K가 (경유) 바뀔 때 기존 멍멍이를 빼주고 새로운 멍멍이를 더해준다.
2. K가 바뀔 때마다 기존 멍멍이 vs 새로운 멍멍이를 비교해준다.

## roads_dog & roads_monkey 에 대한 초기화

- roads_monkey[i][i] 는 Floyd-Warshall 을 위해 0으로 초기화.
roads_dog[i][i] 는 기본 입력 값 mungmunge[i].val 로 초기화.
- roads_monkey[i][j] = INF;  못 가는 경로를 위해 INF으로 초기화.
roads_dog[i][j] = i, j에 있는 mungmunge 최댓 값으로 초기화.
- roads_monkey[a][b] = 입력 받은 경로 c 로 초기화.
roads_dog[a][b] = a, b에 있는 mungmunge 최댓 값으로 초기화.

```cpp
roads_monkey.resize(N+1); for(auto &road : roads_monkey) road.resize(N+1);
roads_dog.resize(N+1); for(auto &road : roads_dog) road.resize(N+1);

for(int i=1; i<=N; i++) {
    int temp;
    cin >> temp;
    mungmunge[i] = {temp, i};
    roads_monkey[i][i] = 0;
    roads_dog[i][i] = mungmunge[i].val;
}

for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
        roads_monkey[i][j] = INF;
        roads_dog[i][j] = max(mungmunge[i].val, mungmunge[j].val);
    }
}

for(int i=1; i<=M; i++) {
    cin >> a >> b >> c;
    roads_dog[a][b] = max(mungmunge[a].val, mungmunge[b].val);
    roads_monkey[a][b] = roads_monkey[b][a] = c;
}

```

## Floyd-Warshall 의 경유지 컨트롤 및 계산.

- 정렬 (멍멍이의 값이 작은 것) 을 통해 경유지 컨트롤.
위의 예시 ) 1 - 2 - 3 - 5 에 가기 전 15가 자꾸 고려되어 최소를 계산할 수 없는 한계 극복.
- **roads_monkey[i][j]** + **roads_dog[i][j]**

    계산되어 있는 [i][j] .

- **roads_monkey[i][k] + roads_monkey[k][j]** + **max(roads_dog[i][k],roads_dog[k][j])**

    경유지 k를 지나는 원숭이의 최소 경로와 그 경유지 중 dog의 최댓 값.

```cpp
sort(mungmunge.begin(), mungmunge.end(), cmp);

void Floyd_Warshall(){
    for(int m=1; m<=N; m++){
        int k= mungmunge[m].idx;
        for(int i=1; i<=N; i++){
            for(int j=1 ;j<=N; j++){
                if(roads_monkey[i][j] + roads_dog[i][j] > roads_monkey[i][k] + roads_monkey[k][j] + max(roads_dog[i][k],roads_dog[k][j])){
                    roads_monkey[i][j] = roads_monkey[i][k] + roads_monkey[k][j];
                    roads_dog[i][j] = max(roads_dog[i][k],roads_dog[k][j]);
                }
            }
        }
    }
}
```

# Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define INF 10000000
#define mINF -10000000
using namespace std;
struct  MUNG{
    int val;
    int idx;
};
vector <MUNG> mungmunge;
vector <vector<int>> roads_monkey;
vector <vector<int>> roads_dog;
int N, M, Q, a, b, c;
bool cmp(const MUNG &a, const MUNG &b){
    return a.val < b.val;
}
void Floyd_Warshall(){
    for(int m=1; m<=N; m++){
        int k= mungmunge[m].idx;
        for(int i=1; i<=N; i++){
            for(int j=1 ;j<=N; j++){
                if(roads_monkey[i][j] + roads_dog[i][j] > roads_monkey[i][k] + roads_monkey[k][j] + max(roads_dog[i][k],roads_dog[k][j])){
                    roads_monkey[i][j] = roads_monkey[i][k] + roads_monkey[k][j];
                    roads_dog[i][j] = max(roads_dog[i][k],roads_dog[k][j]);
                }
            }
        }
    }
}

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q; mungmunge.resize(N+1);
    roads_monkey.resize(N+1); for(auto &road : roads_monkey) road.resize(N+1);
    roads_dog.resize(N+1); for(auto &road : roads_dog) road.resize(N+1);
    for(int i=1; i<=N; i++) {
        int temp;
        cin >> temp;
        mungmunge[i] = {temp, i};
        roads_monkey[i][i] = 0;
        roads_dog[i][i] = mungmunge[i].val;
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            roads_monkey[i][j] = INF;
            roads_dog[i][j] = max(mungmunge[i].val, mungmunge[j].val);
        }
    }
    for(int i=1; i<=M; i++) {
        cin >> a >> b >> c;
        roads_dog[a][b] = max(mungmunge[a].val, mungmunge[b].val);
        roads_monkey[a][b] = roads_monkey[b][a] = c;
    }
    
		sort(mungmunge.begin(), mungmunge.end(), cmp);

    Floyd_Warshall();

    for(int i=1; i<=Q; i++){
        cin >> a >> b;
        cout << (roads_monkey[a][b] == INF? -1 : roads_monkey[a][b] + roads_dog[a][b])<<'\n';
    }
}

int main(){
    input();
}
```

![1602_%E1%84%83%E1%85%A9%E1%84%86%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%A1%20%E1%84%8B%E1%85%AF%E1%86%AB%E1%84%89%E1%85%AE%E1%86%BC%E1%84%8B%E1%85%B5%20971c55ca20c24f5fb4769505bed36a99/Untitled%201.png](1602_%E1%84%83%E1%85%A9%E1%84%86%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%A1%20%E1%84%8B%E1%85%AF%E1%86%AB%E1%84%89%E1%85%AE%E1%86%BC%E1%84%8B%E1%85%B5%20971c55ca20c24f5fb4769505bed36a99/Untitled%201.png)