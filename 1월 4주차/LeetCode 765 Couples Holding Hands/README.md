# LeetCode 765 Couples Holding Hands

#greedy #swap #unordered_map

# Problem

1. **N쌍의 couple이 2N개 의자에 앉아 있다.  (N쌍 커플은 2N명)**
2. **양 옆으로 커플이 앉도록 최소한으로 교체해야 한다.**
3. **Any 스왑 가능. 최소한 이동만 하면 됨.**

# Pre

- 의자 : 0 ~ 2N-1
- 커플 : 0 ~ 2N-1  ⇒  (0,1) , (2,3) ,... ... , (2N-2, 2N-1)
- row (배열) : 4~60 크기
- index : 0부터 순차.

1. **배열을 순차적으로 돈다.**
2. **a라는 숫자 다음에 올 것은??**
    1. a가 짝수 or 0 일 때 : 무조건 a+1
    2. a가 홀수 일 때 : 무조건 a-1
3. **찾아서 바꿔주면 2칸 건너 뛴다.**
4. **어떻게 찾냐? map 이용 (순서 필요없으니 unordered_map이용)**
5. **사람을 swap 해줄 때 마다 answer 증가,  map도 바꿔줘야함.**

# Error

- map을 안바꿨다,,,,,,

---

## Code

```cpp
#include <iostream>
#include <unordered_map>

class Solution {
public:
    int answer = 0;
    unordered_map <int,int> map;
    
    void swapMap(vector<int>& row, int left, int right){
        int temp = map[row[left]];
        map[row[left]] = map[row[right]];
        map[row[right]] = temp;
    }
    
    void swap(vector<int>& row, int left, int right){
        int temp = row[left];
        row[left] = row[right];
        row[right] = temp;
    }
    
    void setMap(vector<int>& row){
        for(int i=0; i<row.size(); i++){
            map[row[i]] = i;
        }
    }
    
    int minSwapsCouples(vector<int>& row) {
        
        setMap(row);
        
        for(int i=0; i<row.size()-1; i+=2){
            int nextIdx;
            if(row[i]%2==0){
                if(row[i+1] == row[i]+1) continue;
                nextIdx = map[row[i]+1];
            }else{
                if(row[i+1] == row[i]-1) continue;
                nextIdx = map[row[i]-1];
            }
            swap(row, i+1, nextIdx);
            swapMap(row, i+1, nextIdx);
            answer+=1;
        }
        
        return answer;
    }
};
```

![LeetCode%20765%20Couples%20Holding%20Hands%20e388fdad3be542f3a446ef752216efe9/LeetCode_765_Couples_Holding_Hands.png](LeetCode%20765%20Couples%20Holding%20Hands%20e388fdad3be542f3a446ef752216efe9/LeetCode_765_Couples_Holding_Hands.png)