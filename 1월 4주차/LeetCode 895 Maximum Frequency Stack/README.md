# LeetCode 895 Maximum Frequency Stack

# 문제이해

1. **FreqStack을 구현하라.**
    - 자료구조 stack과 유사한 class이다.
2. **멤버함수 2개를 구현하라.**
    - push(int x) :

           x : integer  return X

    - pop() :

          **가장 많은 빈도 수를 가진 element를 반환하라.**

          **빈도 수가 같은 것이 있으면 LIFO 하라.**

          return integer;

# 제한사항

- 10^9 = 1,000,000,000
- empty일 때 pop() 은 없다.
- 함수 콜이 대충 10,000번 이하다

# Pre

- Push 할 때, element의 갯수 체크.
- Pop 할 때, element의 갯수가 most인 것.

    element 별 갯수 체크 및 확인을 어떻게?

    1. map

        [element] : [cnt] 로 하면 알 수 있다.
        + cnt 기준 내림차순으로 정렬.

    2. priority queue

        넣어놓고 증가하면 그 전 값들이 남아 있어서 안됨.

⇒ 

![LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled.png](LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled.png)

1. 가장 큰 값이 몇 인가?
2. 가장 늦게 들어 온 수 부터 1번에 해당하는 요소는 무엇인가?
3. 반환 과 후처리
    1. Map value 줄이기
    2. 가장 큰 값 줄이거나 유지.
    3. vector 줄이거나 제거

# Error

1. Vector 탐색에서 시간초과가 나는 것 같다.
2. map → unordered_map으로 바꾸자

# Better Solve

![LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%201.png](LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%201.png)

1. **어떤게 Top과 가까운 element이고 MostFrequency를 만족하는지?**

    기존 : vector 를 뒤부터 탐색

    → 개선 필요

    < push >

    ![LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%202.png](LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%202.png)

    < pop >

    ![LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%203.png](LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/Untitled%203.png)

    **줄여줄 필요가 없다.  언젠가  global이 4개일 때 쓰겠지**

# Push

```cpp
void push(int x) {
  int xCnt = ++elemCountMap[x];
  global = (global < xCnt ? xCnt : global);
	countStackMap[xCnt].push(x);
}
```

- element : cnt  로 이루어진 Map 관리.
- MostFrequency  변수 관리.
- Stack 관리.

# Pop

```cpp
int pop() {
    int element = countStackMap[global].top(); countStackMap[global].pop(); 
    if(countStackMap[global].size() == 0) global --;
    elemCountMap[element]--;
    return element;
}
```

- 가장 Top에 가까운 MostFrequency Elem을 찾는 과정.
- stack이 비면 같은 MostFrequency 다른 elem은 없다.

    → global 감소

- element : cnt 로 이루어진 Map 관리.
- 해당 요소 반환.

# Code

```cpp
#include <iostream>
#include <unordered_map>
#include <stack>

class FreqStack {
public:
    int global;
    unordered_map <int,int> elemCountMap;
    unordered_map <int,stack<int> > countStackMap;
    FreqStack() {
        
    }
    
    void push(int x) {
        int xCnt = ++elemCountMap[x];
        global = (global < xCnt ? xCnt : global);
        countStackMap[xCnt].push(x);
    }
    
    int pop() {
        int element = countStackMap[global].top(); countStackMap[global].pop();
        if(countStackMap[global].size() == 0) global --;
        elemCountMap[element]--;
        return element;
    }
};
```

![LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/LeetCode_895_Maximum_Frequency_Stack.png](LeetCode%20895%20Maximum%20Frequency%20Stack%20fc20e8dc54884deb9ffc4e16c66f16dc/LeetCode_895_Maximum_Frequency_Stack.png)