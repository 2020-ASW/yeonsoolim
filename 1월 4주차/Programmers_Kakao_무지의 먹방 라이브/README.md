# 무지의 먹방 라이브

계산, 머리굴리기

# Pre

K : 시간  N : 남은 음식 수

1. K 시간이 되기 전 몇 개의 음식이 줄어들었는가?
2. 배열 N개 일 때 : 
K는 K/N바퀴를 돌고, K%N번째에 있는 음식에 있다.
3. 모든 음식이 K/N 만큼 사라지고, 
0~K%N번째 까지는 1번 더 사라진다.
4. 중간에 소모되면 1바퀴 도는 시간도 줄어든다.
5. K 는 20조 → K번 돌 수 없다.

![%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled.png](%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled.png)

# 주의 사항

- 다음 지울 요소  minFood를 모른다?
- X 바퀴를 돈 후,  Vector의 요소들을 지운다??
→ X
- **마지막에 가르키는 곳에 Index를 알 수 있어야 한다.**

    남은 음식이 몇 번 음식인가.

- ~~min을 다 구해놓는다. Histogram 처럼.~~

    ~~map  ⇒   [ 소요 시간 ] : [몇 개]~~

    ~~여러 바퀴를 1번에 계산해버리기.~~

- min 을 다 구해놓는다.

    vector →  [ 값 ] , [ Index ]

    한 번에 배열 크기만큼만 계산.

# Solve

1. 소요시간이 짧은 것 부터 먹어 치운다.

    이때,  K : 시간이 줄고,  N : 남은 음식이 줄어든다. 여러개 X 1개씩 O

2. 언제 멈추냐
    1. 남은 음식이 없을 때 : 

        이건 totalFoodTime이 처음 K 보다 크다면 무조건 -1이다.

    2. 다음 먹어치울 음식 min 이 남은 K보다 크다면 마지막 바퀴다.

        K % N 으로 해결된다.

3. 멈출 때 번호 구하기. pair 에 넣어놨다.
4. 감소되는 것을 처리 해주어야 한다.

    썼던 minFood 값을 기억해뒀다가 다음 minFood와 차를 구한다.

![%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled%201.png](%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled%201.png)

- **-1 이 될 케이스 처리**

    ```cpp
    bool outOfTotal(vector<int> food_times, long long k){
        ll total = 0;
        for(int i=0; i<food_times.size(); i++) total += food_times[i];   
        if(total <= k) return true;
        return false;
    }

    if(outOfTotal(food_times, K)) return -1;
    ```

- **먼저 사라질 순서대로 음식을 정렬해준다.**

    ![%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled%202.png](%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/Untitled%202.png)

    ```cpp
    sort(histogram.begin(), histogram.end(), cmp);
    ```

- K가 적정 수 까지 줄어들도록 계속 돌아준다.
    - cnt 를 체크해 몇 가지 음식이 사라졌는지를 알아야 한다.
    - 다음 minFood 는  minFood - acc 이다. 도는 동안 수가 줄어들기 때문.
    - K (시간) 은 minFood * 배열 크기 ⇒ 한바퀴 만큼 줄어든다.
    - N (종류) 는 minFood 하나를 먹어치우면 하나가 사라진다.

    ```cpp
    while(1){
        cnt++;
        minFood = histogram[cnt].first - acc;
        acc += minFood;
        
        if(minFood * N >= K){  // 이 안은 한바퀴 돌기전에 끝난다.
            sort(histogram.begin()+cnt, histogram.end(), cmp2);
            return histogram[cnt+(K%N)].second;
        }
        K -= (minFood * N);
        N -= 1; 
    }
    ```

# Code

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#define ll long long

using namespace std;
vector <pair<int,int> > histogram;
bool cmp(const pair<int,int> &a, const pair<int,int> &b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}
bool cmp2(const pair<int,int> &a, const pair<int,int> &b){
    return a.second < b.second;
}
bool outOfTotal(vector<int> food_times, long long k){
    ll total = 0;
    for(int i=0; i<food_times.size(); i++) total += food_times[i];   
    if(total <= k) return true;
    return false;
}
void setHistogram(vector<int> food_times){
    for(int i=0; i<food_times.size(); i++){
        histogram.push_back({food_times[i],i+1});
    }
}
int solution(vector<int> food_times, long long k) {
    int N = food_times.size();
    ll K = k;
    if(outOfTotal(food_times, K)) return -1;
    setHistogram(food_times);
    
    ll minFood, minFoodCnt, acc = 0;
    sort(histogram.begin(), histogram.end(), cmp);
    int cnt = -1;
    while(1){
        cnt++;
        minFood = histogram[cnt].first - acc;
        acc += minFood;
        
        if(minFood * N >= K){  
            sort(histogram.begin()+cnt, histogram.end(), cmp2);
            return histogram[cnt+(K%N)].second;
        }
        K -= (minFood * N);
        N -= 1; 
          
    }
}
```

![%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/PNG__5.png](%E1%84%86%E1%85%AE%E1%84%8C%E1%85%B5%E1%84%8B%E1%85%B4%20%E1%84%86%E1%85%A5%E1%86%A8%E1%84%87%E1%85%A1%E1%86%BC%20%E1%84%85%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%87%E1%85%B3%201a62ba3cc1064a5a973776594cbbe1bc/PNG__5.png)