# Programmers 67258 보석 쇼핑

# 제한사항

- gems 배열 크기 : 1 ~ 100,000
- gem 원소 길이 : 10 이하 문자열

# Pre

1. **일단 몇 종류의 gem이 있는지 알 수 없다.**

    ⇒ Hash 가 필요할 것 같다. set or map

2. **gem이 모두 선택되는 구간을 구하면 될 것 같다.**

    ⇒ 세그 트리   or  투포인터

    ![Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Untitled.png](Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Untitled.png)

    ![Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Untitled%201.png](Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Untitled%201.png)

    1. **gem의 종류 수 를 구한다.**

        map ⇒ {  gem : string,  index : int }

        ```cpp
        unordered_map <string,int> map;

        void setMap(vector<string> gems){
            for(auto &gem : gems){
                if(map.find(gem) != map.end()) continue;
                map.insert({gem, map.size()});
            }
        }
        ```

    2. **투포인터를 통해 구간에서 모든 종류의 gem이 있는 구간을 구한다.**
        - bitset <100001> 을 이용하여 gem 1개당 1bit로 visit 체크를 한다.

        ```cpp
        while(1){
        		if(visit.count() == map.size()){
        			  left 를 옮긴다.
        				// visit이 map보다 커질일은 없다.
        		}
        		else if(right == map.size()) 멈춘다;
        		else{
        		    right 를 옮긴다.
        		}
        }
        ```

    3. **가장 짧은 길이의 구간 & 가장 앞에 있는 구간을 구한다.**

        ```cpp
        candidate.push_back({left+1,right+1});

        int length = 2147483647;
            vector <int> answer;
            for(auto iter=candidate.begin(); iter!=candidate.end(); ++iter){
                if(length > (iter->second - iter->first)){
                    length = (iter->second - iter->first);
                    answer.clear();
                    answer.push_back(iter->first);
                    answer.push_back(iter->second);
                }
            }
            return answer;
        ```

    # Error

    1. **right pointer를 ++한 후, gems의 index를 참조하기 때문에 범위를 벗어날 수 있다.** 
    ⇒ 이에 해당할 때 break;
    2. **left pointer를 옮긴 후, 없앤 gem에 해당하는 visit bit를 지웠는데,
    옮긴 left  ~~ right 사이에 같은 gem이 더 있을 수 있다.**
    ⇒ 중복 체크를 해주어야 한다.

        ```cpp
        vector <int> duplicate;
        duplicate[map[gems[0]]]++;

        // left 옮길 때
        	duplicate[map[gems[left]]]--;
          if(duplicate[map[gems[left]]] == 0)
              visit.reset(map[gems[left]]);
          left++;

        // right 옮길 때
        	duplicate[map[gems[right]]]++;
        	if(visit.test(map[gems[right]]) == false){
        	    visit.set(map[gems[right]]);
        	}
        ```

    ---

    ### 효율성 시간초과 해결하기.

    1. **3번의 조건을 만족하는 정답은 투포인터 도중에도 구할 수 있다.**
    ⇒ 길이가 가장 짧은 것 중 처음 들어가는 것만 구하면 된다.

        ```cpp
        int minimum = 2147483647;
        while(1){
        		... ...
        		if((right-left)<minimum){
                answer.clear();
                answer.push_back(left+1);
                answer.push_back(right+1);
                minimum = (right-left);
            }
        		... ...
        }
        ```

    2. **left ~ N (gems배열 끝) 까지 길이가 map.size() 보다 작으면 볼 필요가 없다.**

        ?? 이게뭐더라

        ```cpp
        if(gems.size()-left < map.size()) break;
        ```

    3. **바로 끝나는 케이스를 구현해주어야 한다.**

        ```cpp
        if(token.size() == 1){
        	  vector <int> answer(2,1);
        	  return answer;
        } 
        ```

    4. **bitMask 100001개, duplicate 100001개를 합쳐야 한다.**
        - get한 보석 종류의 수
        - get한 보석 중 같은 종류의 수

        ```cpp
        //bitset <100001> visit;
        //vector <int> duplicate;
        => 
        unordered_map <int, int> visit;
        ```

# Code

```cpp
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

unordered_map <string,int> token;
unordered_map <int, int> visit;

void setToken(vector<string> gems){
    for(auto &gem : gems){
        if(token.find(gem) != token.end()) continue;
        token.insert({gem, token.size()});
    }
}
vector<int> twoPointer(vector<string> gems){
    vector <int> answer;
    int left = 0, right = 0;
    visit[token[gems[0]]]++;
    int minimum = 2147483647;
    while(1){ 
        if(visit.size() ==token.size()){
            if((right-left)<minimum){
                answer.clear();
                answer.push_back(left+1);
                answer.push_back(right+1);
                minimum = (right-left);
            }
            visit[token[gems[left]]]--;
            if(visit[token[gems[left]]] == 0)
                visit.erase(token[gems[left]]);
            left++;
        }
        else if(right == gems.size()) break;
        else{
            ++right; if(right>=gems.size())break;
            visit[token[gems[right]]]++;
        }
        if(gems.size()-left < token.size()) break;
    }
    
    return answer;
}
vector<int> solution(vector<string> gems) {
    setToken(gems);
    if(token.size() == 1){
        vector <int> answer(2,1);
        return answer;
    } 
    return twoPointer(gems);
}
```

![Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Programmers_67258__.png](Programmers%2067258%20%E1%84%87%E1%85%A9%E1%84%89%E1%85%A5%E1%86%A8%20%E1%84%89%E1%85%AD%E1%84%91%E1%85%B5%E1%86%BC%20e526de0813e14742a03f86e2f72ef7ff/Programmers_67258__.png)