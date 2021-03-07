# Programmers N으로 표현

# Problem

### **문제 설명**

아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)12 = 55 / 5 + 5 / 512 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법 중 N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

# Pre

1. 더하기, 빼기, 곱하기, 나누기 와  *11 로 할 줄 알았으나,,, 
* 11, *111, *1111 은 N 일 때만 적용 될 뿐...

# Solve

1. 연산 없이 가능한 수 구하기.

    ```cpp
    void make8kindOfN(unordered_set <int> &items, int cnt, int N){
        string eleven = "1";
        for(int i=0; i<cnt; i++) eleven += "1";
        items.insert(N*stoi(eleven));
    }
    int solve(int N, int number){
        vector <unordered_set <int>> items(8);
        for(int i=0; i<8; i++){
            items[i].clear();
            make8kindOfN(items[i], i, N);
        }
    		...
    }
    ```

2. 가능한 수들로 연산 하기.

![Programmers%20N%E1%84%8B%E1%85%B3%E1%84%85%E1%85%A9%20%E1%84%91%E1%85%AD%E1%84%92%E1%85%A7%E1%86%AB%20017bb93a712d4543a8938a183ffc11da/Untitled.png](Programmers%20N%E1%84%8B%E1%85%B3%E1%84%85%E1%85%A9%20%E1%84%91%E1%85%AD%E1%84%92%E1%85%A7%E1%86%AB%20017bb93a712d4543a8938a183ffc11da/Untitled.png)

```cpp
for(int i=1; i<8; i++){
    for(int j=0; j<i; j++){        
        for(auto &left : items[j]){
            for(auto &right : items[i-j-1]){
                items[i].insert(left*right);
                items[i].insert(left+right);
                items[i].insert(left-right);
                if(right == 0) continue;
                items[i].insert(left/right);
            }
        }
    }    
    if(items[i].find(number) != items[i].end()){
        return i+1;
    }
}
```

- i = 몇 개를 사용할 것인가
- j =  i개를 표현하기 위한 그 아랫 수.
- left & right : 연산을 할 때 사용할 수

# Code

```cpp
#include <string>
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;

void make8kindOfN(unordered_set <int> &items, int cnt, int N){
    string eleven = "1";
    for(int i=0; i<cnt; i++) eleven += "1";
    items.insert(N*stoi(eleven));
}
int solve(int N, int number){
    vector <unordered_set <int>> items(8);
    for(int i=0; i<8; i++){
        items[i].clear();
        make8kindOfN(items[i], i, N);
    }
    for(int i=1; i<8; i++){
        for(int j=0; j<i; j++){        
            for(auto &left : items[j]){
                for(auto &right : items[i-j-1]){
                    items[i].insert(left*right);
                    items[i].insert(left+right);
                    items[i].insert(left-right);
                    if(right == 0) continue;
                    items[i].insert(left/right);
                }
            }
        }    
        if(items[i].find(number) != items[i].end()){
            return i+1;
        }
    }
    return -1;
}
int solution(int N, int number) {
    if(N==number) return 1;
    else return solve(N, number);
}
```

![Programmers%20N%E1%84%8B%E1%85%B3%E1%84%85%E1%85%A9%20%E1%84%91%E1%85%AD%E1%84%92%E1%85%A7%E1%86%AB%20017bb93a712d4543a8938a183ffc11da/Untitled%201.png](Programmers%20N%E1%84%8B%E1%85%B3%E1%84%85%E1%85%A9%20%E1%84%91%E1%85%AD%E1%84%92%E1%85%A7%E1%86%AB%20017bb93a712d4543a8938a183ffc11da/Untitled%201.png)