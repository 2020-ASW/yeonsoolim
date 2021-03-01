# Programmers 입국 심사

# Solve

1. 심사원이 있고, 대기자가 있을 때 몇 분 안에 모든 대기자가 심사를 볼 수 있는가?

    ⇒ 최대 시간 ~ 1 분 사이에 이분 탐색을 진행한다.

### 시간을 줄이기 위한 아이디어

1. times 배열을 sort후 이분탐색에 대해 check할 때, 0~ upper_bound까지 체크 하면 되지 않을까?

    ⇒ Sort를 넣는 순간 50ms 까지 가거나 대충 10ms 더 늘어난다.

2. 최대 시간 (이분탐색의 right)부분을 줄여보자.

    기존 : (ll)n*(*max_element(times.begin(), times.end()))
    개선 : 

    int cycle = n/times.size();
    return (ll)cycle*(*max_element(times.begin(), times.end()));

    ⇒ 가장 오래 걸리는 심사원이 다 맡는다 * 대기자 수  ≥ 모든 심사원이 1명 씩 맡는다 * (병렬)

    ⇒ 48ms → 39ms

# Error

함수 반환을 ll 로 안하고 int로 한 걸 못발견해서 엄청 해맸다..

# Code 1st

```cpp
#include <string>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

ll solution(int n, vector<int> times) {
    ll answer = 0;
    
    ll start = 1; ll end = (ll)n*(*max_element(times.begin(), times.end()));
    while(end-start >= 0){
        ll mid = (start+end)/2;
        ll processed = 0;
        for(int i=0; i<times.size(); i++) processed += mid/(ll)times[i];
        if(processed >= n){
            answer = mid;
            end = mid - 1;
        }
        else start = mid +1;
         
    }
    
    return answer;
}
```

# Code 2nd

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define ll long long
using namespace std;
ll getMaxtime(int n, vector<int> &times){
    int cycle = n/times.size();
    return (ll)cycle*(*max_element(times.begin(), times.end()));
}
bool check(ll mid, int n, vector<int> &times){
    ll total = 0;
    for(ll i= 0; i < times.size(); i++){
        total += mid/(ll)times[i]; 
    }
    return total>=n;
}
ll binarySearch(int n, vector<int> &times){
    ll MAXTIME = getMaxtime(n, times);

    ll left = 1, right = MAXTIME, answer = 0;
    while(left <=right){
        ll mid = (right-left)/2 + left;
        
        if(check(mid, n, times)){
            right= mid-1;
            answer = mid;
        }else{
            left = mid+1;
        }
    }
    return answer;
}

long long solution(int n, vector<int> times) {    
    ll answer = binarySearch(n, times);
    
    return answer;
}
```