# 외벽점검

계산, 머리굴리기

# 문제 설명

### **문제 설명**

레스토랑을 운영하고 있는 **스카피**는 레스토랑 내부가 너무 낡아 친구들과 함께 직접 리모델링 하기로 했습니다. 레스토랑이 있는 곳은 스노우타운으로 매우 추운 지역이어서 내부 공사를 하는 도중에 주기적으로 외벽의 상태를 점검해야 할 필요가 있습니다.

레스토랑의 구조는 **완전히 동그란 모양**이고 **외벽의 총 둘레는 n미터**이며, 외벽의 몇몇 지점은 추위가 심할 경우 손상될 수도 있는 **취약한 지점들**이 있습니다. 따라서 내부 공사 도중에도 외벽의 취약 지점들이 손상되지 않았는 지, 주기적으로 친구들을 보내서 점검을 하기로 했습니다. 다만, 빠른 공사 진행을 위해 점검 시간을 1시간으로 제한했습니다. 친구들이 1시간 동안 이동할 수 있는 거리는 제각각이기 때문에, 최소한의 친구들을 투입해 취약 지점을 점검하고 나머지 친구들은 내부 공사를 돕도록 하려고 합니다. 편의 상 레스토랑의 정북 방향 지점을 0으로 나타내며, 취약 지점의 위치는 정북 방향 지점으로부터 시계 방향으로 떨어진 거리로 나타냅니다. 또, 친구들은 출발 지점부터 시계, 혹은 반시계 방향으로 외벽을 따라서만 이동합니다.

외벽의 길이 n, 취약 지점의 위치가 담긴 배열 weak, 각 친구가 1시간 동안 이동할 수 있는 거리가 담긴 배열 dist가 매개변수로 주어질 때, 취약 지점을 점검하기 위해 보내야 하는 친구 수의 최소값을 return 하도록 solution 함수를 완성해주세요.

### **제한사항**

- n은 1 이상 200 이하인 자연수입니다.
- weak의 길이는 1 이상 15 이하입니다.
    - 서로 다른 두 취약점의 위치가 같은 경우는 주어지지 않습니다.
    - 취약 지점의 위치는 오름차순으로 정렬되어 주어집니다.
    - weak의 원소는 0 이상 n - 1 이하인 정수입니다.
- dist의 길이는 1 이상 8 이하입니다.
    - dist의 원소는 1 이상 100 이하인 자연수입니다.
- 친구들을 모두 투입해도 취약 지점을 전부 점검할 수 없는 경우에는 -1을 return 해주세요.

# Pre

1. **Binary Search  ( mid = 투입 될 인원)** 
2. **GAP을 구한다.   GAP ⇒ 주어진 weak배열에서  한 점에서 다른 한 점까지의 거리.**
3. **투입된 인원이 GAP을 모두 커버할 수 있는가?**

    ![%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled.png](%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled.png)

# ⇒ Fail.

1. 현재 Logic은 무조건 점을 건너뛴다는 가정하에 이루어짐.
투입된 인원의 dist에 따라서 연속하여 점을 지나가는 경우가 있다.

# Solve

1. **~~투입 인원은 무조건 dist가 긴 friend를 쓰면 될 것 같다. 정렬~~**

    ```cpp
    sort(dist.begin(), dist.end(), cmp);
    ```

2. **weak를 줄 세워, 시작지점을 바꿔준다.**

    ```cpp
    for(int start=0; start<weak.size(); start++){
        vector <int> weaksOrder;
        
    		for(int next= start; next<weak.size()+start; next++){
            weaksOrder.push_back(weak[next%weak.size()]);
        }

        reverse(weaksOrder.begin(), weaksOrder.end());  
    }
    ```

    ![%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%201.png](%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%201.png)

3. **friends와 weaks를 구했다.**
    - weaks 배열에 따른 다음 거리를 구한다.

        ```cpp
        int getNextDistance(bool reverse, int n, int w, vector<int> &weaksOrder){
            int nextDistance = weaksOrder[w+1] - weaksOrder[w];
            
        		if(!reverse && weaksOrder[w] > weaksOrder[w+1]) 
        				nextDistance += n;
            else if(reverse && weaksOrder[w]> weaksOrder[w+1]) 
        				nextDistance = abs(nextDistance);
            else if(reverse && nextDistance > 0) 
        				nextDistance = n - nextDistance; 

            return nextDistance;
        }
        ```

        ![%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%202.png](%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%202.png)

    - friends가 갈 수 있는 최대 거리를 간다.
    - 다음 지점에 도달 했을 때  :
        - 더 갈 수 있는가?  ⇒ 현재 지점과, 다음 지점을 Check 후, 다음 지점으로 이동한다.
        - 더 못 가는가?  ⇒  현재 지점과, 다음 지점을 Check 후, 다음 다음 지점으로 Pointer를 옮기고 다른 friends를 부른다.
    - 다음 지점에 미치지 못했을 때 :
        - 현재 지점은 도착했으므로, 다음 지점으로 Pointer를 옮겨준다.

    ```cpp
    int w = 0;
    unordered_set <int> set;
    for(int i=0; i<friends.size(); i++){
        int range = friends[i];
        int nextDistance;
        while(range>0){
            nextDistance = getNextDistance(reverse, n, w, weaksOrder);
       
    		    if(nextDistance <= range){
                range -= nextDistance;
                set.insert(w);
                set.insert(w+1);
                
    						if(range>0) w++;
                else w+=2;
            }else{
                set.insert(w);
                w++;
                break;
            } 
            if(set.size() >= weaksOrder.size()) return true;
        }
        if(set.size() >= weaksOrder.size()) return true;
    }
    ```

    ![%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%203.png](%E1%84%8B%E1%85%AC%E1%84%87%E1%85%A7%E1%86%A8%E1%84%8C%E1%85%A5%E1%86%B7%E1%84%80%E1%85%A5%E1%86%B7%20a18543a3ebe743dcadee2419dacd6bb6/Untitled%203.png)

4. **Check된 지점을 set에 넣어 만족했는지 확인한다.**
5. **성공했다면 투입인원을 줄여주고, 
실패했다면 투입인원을 늘려준다.**

    ```cpp
    int left = 1, right = dist.size();
    while(left <= right){
        int mid = (right-left)/2 + left;  
        if(support(mid, n, weak, dist)){
            right = mid-1;
            answer = (answer > mid ? mid: answer);
        }else{
            left = mid+1;
        }
    }
    ```

## CheckPoint

- n : 판의 크기 가 ≤ 2 라면 무조건 1명으로 갈 수 있다.
- dist[0] 가 n 보다 크다면 혼자서 다 갈 수 있다.

    ```cpp
    if(n <= 2) return 1;
    if(n <= dist[0]) return 1;
    ```

- 투입 인원과 weak 갯수가 같다면 무조건 해결 할 수 있다.

    ```cpp
    if(friends.size() >= weaksOrder.size()) return true;
    ```

아래 14번 TC 만 실패하는 경우  Friends 도 모든 순열을 구해주어야 함.

1번째 시도에서는  sort 한 후, dist가 큰 것만 넣어서 fail

2번째 시도에서는 bitmask로 조합을 구했기 때문에 fail

⇒ vector [depth] 에 순서대로 넣어서 모든 순열을 구해줌.

# 2nd Try  14⇒ Fail

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

int calcDistance(bool CCW, int &N, vector<int> &weaks, int curr){
    int nextDistance = 0;
    if(!CCW){
        if(weaks[curr+1] < weaks[curr])  // 12 -> 
            nextDistance = weaks[curr+1]+N - weaks[curr]; 
        else
            nextDistance = weaks[curr+1] -weaks[curr];
    }else{
        if(weaks[curr+1] > weaks[curr])  //  <- 12 
            nextDistance = N - weaks[curr+1] + weaks[curr]; 
        else
            nextDistance = abs(weaks[curr] - weaks[curr+1]);     
    }
    
    return nextDistance;
}

bool check(bool CCW, int &N, vector<int> &weaks, vector<int> &friends){
    bool success = false;
    int nextDistance = 0;
    
    int curr = 0;
    int completed = 0;
    int _friend = 0;
    int friendIdx = 0;
    
    while(1){
        if(_friend <= 0) _friend = friends[friendIdx];
        nextDistance = calcDistance(CCW,N, weaks, curr);
       
        if(_friend < nextDistance){
            completed += 1;
            curr += 1; 
            _friend = 0;
            friendIdx+=1;
        }else if(_friend == nextDistance){
            completed += 2;
            curr += 2;
            _friend = 0;
            friendIdx+=1;
        }else if(_friend > nextDistance){
            completed += 1;
            curr += 1;
            _friend = _friend-nextDistance;
            friendIdx = friendIdx;
        }
        if(completed >= weaks.size()){
            return true;
        }
        if(friendIdx >= friends.size() || curr >= weaks.size()){
            return false;
        }
    }
    if(completed >= weaks.size()) return true;
    else return false;
}

bool assignFriends(bool CCW, int &N, int &numFriends, bitset <8> bits, vector<int> &weaks, vector<int> &dist){
    if(bits.count() == numFriends){
        vector<int> friends;
        for(int i=0; i<8; i++)
            if(bits.test(i)) 
                friends.push_back(dist[i]);
        
        
        return check(CCW, N, weaks, friends);
    }

    for(int i=0; i<dist.size(); i++){
        if(bits.test(i)) continue;
        bool result = false;
        result = assignFriends(CCW, N, numFriends, bits.set(i), weaks, dist);
        if(result) return true;
        bits.reset(i);
    }
    return false;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    reverse(dist.begin(), dist.end());
    for(int numFriends = 1; numFriends<=dist.size(); numFriends++){
        if(numFriends >= weak.size()) return numFriends;
        //weak의 배열 조작
        for(int pos = 0; pos<weak.size(); pos++){
            vector<int> newWeak;
            bitset <8> friends;
            bool result = false;
            
            // CW
            for(int i=pos; i<weak.size()+pos; i++)
                newWeak.push_back(weak[i%weak.size()]);
            result = assignFriends(false, n, numFriends, friends, newWeak, dist);
            if(result) return numFriends;
            
            // CCW
            reverse(newWeak.begin(), newWeak.end());
            result = assignFriends(true, n, numFriends, friends, newWeak, dist);
            if(result) return numFriends;
       }        
    }
    
    return -1;
}
```

# 2nd Try  Success

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

int calcDistance(bool CCW, int &N, vector<int> &weaks, int curr){
    int nextDistance = 0;
    if(!CCW){
        if(weaks[curr+1] < weaks[curr])  // 12 -> 
            nextDistance = weaks[curr+1]+N - weaks[curr]; 
        else
            nextDistance = weaks[curr+1] -weaks[curr];
    }else{
        if(weaks[curr+1] > weaks[curr])  //  <- 12 
            nextDistance = N - weaks[curr+1] + weaks[curr]; 
        else
            nextDistance = abs(weaks[curr] - weaks[curr+1]);     
    }
    
    return nextDistance;
}

bool check(bool CCW, int &N, vector<int> &weaks, vector<int> &friends){
    bool success = false;
    int nextDistance = 0;
    
    int curr = 0;
    int completed = 0;
    int _friend = 0;
    int friendIdx = 0;
    
    while(1){
        if(_friend <= 0) _friend = friends[friendIdx];
        nextDistance = calcDistance(CCW,N, weaks, curr);
        
        if(_friend < nextDistance){
            completed += 1;
            curr += 1; 
            _friend = 0;
            friendIdx+=1;
        }else if(_friend == nextDistance){
            completed += 2;
            curr += 2;
            _friend = 0;
            friendIdx+=1;
        }else if(_friend > nextDistance){
            completed += 1;
            curr += 1;
            _friend = _friend-nextDistance;
            friendIdx = friendIdx;
        }
        if(completed >= weaks.size()){
            return true;
        }
        if(friendIdx >= friends.size() || curr >= weaks.size()){
            return false;
        }
    }
    if(completed >= weaks.size()) return true;
    else return false;
}

bool assignFriends(bool CCW, int &N, int &numFriends, bitset <8> bits, vector<int> friends, vector<int> &weaks, vector<int> &dist){
    if(bits.count() == numFriends){
        // vector<int> friends;
        // for(int i=0; i<8; i++)
        //     if(bits.test(i)) 
        //         friends.push_back(dist[i]);
       
        return check(CCW, N, weaks, friends);
    }

    for(int i=0; i<dist.size(); i++){
        if(bits.test(i)) continue;
        bool result = false;
        bits.set(i);
        friends[bits.count()-1] = dist[i];
        result = assignFriends(CCW, N, numFriends, bits, friends, weaks, dist);
        bits.reset(i);
        if(result) return true;
    }
    return false;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    reverse(dist.begin(), dist.end());
    for(int numFriends = 1; numFriends<=dist.size(); numFriends++){
        if(numFriends >= weak.size()) return numFriends;
        //weak의 배열 조작
        for(int pos = 0; pos<weak.size(); pos++){
            vector<int> newWeak;
            bitset <8> bits;
            vector <int> friends(numFriends,0);
            bool result = false;
            
            // CW
            for(int i=pos; i<weak.size()+pos; i++)
                newWeak.push_back(weak[i%weak.size()]);
            result = assignFriends(false, n, numFriends, bits, friends, newWeak, dist);
            if(result) return numFriends;

            // CCW
            reverse(newWeak.begin(), newWeak.end());
            result = assignFriends(true, n, numFriends, bits, friends, newWeak, dist);
            if(result) return numFriends;
       }        
    }
    
    return -1;
}
```

# 1st Try    ???    ⇒ 14번 Fail

- 사실 weaks가 모든 경우가 다있는데, (Reverse 포함) friends는 순열을 구하지 않고 큰 순서대로만 넣으면 되지 않을까?

```cpp
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <stdlib.h>
#define uint unsigned int
using namespace std;
bool cmp(const int &a, const int &b){
    return a>b;
}
int getNextDistance(bool reverse, int n, int w, vector<int> &weaksOrder){
    int nextDistance = weaksOrder[w+1] - weaksOrder[w];
    if(!reverse && weaksOrder[w] > weaksOrder[w+1]) nextDistance += n;
    else if(reverse && weaksOrder[w]> weaksOrder[w+1]) nextDistance = abs(nextDistance);
    else if(reverse && nextDistance > 0) nextDistance = n - nextDistance; 
    return nextDistance;
}
   
bool calc(bool reverse, int mid, int n, vector<int> &dist, vector<int> &weaksOrder){
    unordered_set <int> set;
    int w = 0;
    for(int i=0; i<mid; i++){
        int range = dist[i];
        while(range>0){
            int nextDistance = getNextDistance(reverse, n, w, weaksOrder);
            set.insert(w++);
            if(nextDistance <= range){
                range -= nextDistance;
                set.insert(w);
                if(range == 0) w++;
            }else break;
            
            if(set.size() >= weaksOrder.size()) return true;
        }
        if(set.size() >= weaksOrder.size()) return true; 
    }
    if(set.size() >= weaksOrder.size()) return true;
    return false;
}
bool support(int mid, int n, vector<int> &weak, vector<int> &dist){
    for(int start=0; start<weak.size(); start++){
        vector <int> weaksOrder;
        for(int next= start; next<weak.size()+start; next++){
            weaksOrder.push_back(weak[next%weak.size()]);
        }
        if(mid >= weaksOrder.size()) return true;
        bool res = calc(false, mid, n, dist, weaksOrder);
        if(res) return true;
        reverse(weaksOrder.begin(), weaksOrder.end());
        res = calc(true, mid, n, dist, weaksOrder);
        if(res) return true;        
    }
    return false;
}

void binarySearch(int &answer, int n, vector<int> &weak, vector<int> &dist){
    int left = 1, right = dist.size();
    while(left <= right){
        int mid = (right-left)/2 + left;  
        if(support(mid, n, weak, dist)){
            right = mid-1;
            answer = (answer > mid ? mid: answer);
        }else{
            left = mid+1;
        }
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    if(n <= 2) return 1;
    
    int answer = 2147483647;
    sort(dist.begin(), dist.end(), cmp);
    if(n <= dist[0]) return 1;
    binarySearch(answer, n, weak, dist);
    
    return (answer == 2147483647 ? -1 : answer);
}
```

# Code 2

```cpp
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <stdlib.h>
#define uint unsigned int
using namespace std;
bool cmp(const int &a, const int &b){
    return a>b;
}
int getNextDistance(bool reverse, int n, int w, vector<int> &weaksOrder){
    int nextDistance = weaksOrder[w+1] - weaksOrder[w];
    if(!reverse && weaksOrder[w] > weaksOrder[w+1]) nextDistance += n;
    else if(reverse && weaksOrder[w]> weaksOrder[w+1]) nextDistance = abs(nextDistance);
    else if(reverse && nextDistance > 0) nextDistance = n - nextDistance; 
    return nextDistance;
}
bool calc(bool reverse, int n, vector<int> friends, vector<int> &weaksOrder){
    int w = 0;
    unordered_set <int> set;
   
    for(int i=0; i<friends.size(); i++){
        int range = friends[i];
        int nextDistance;
        while(range>0){
            nextDistance = getNextDistance(reverse, n, w, weaksOrder);
          
            if(nextDistance <= range){
                range -= nextDistance;
                set.insert(w);
                set.insert(w+1);
                if(range>0) w++;
                else w+=2;
            }else{
                set.insert(w);
                w++;
                break;
            } 
            if(set.size() >= weaksOrder.size()) return true;
        }
        if(set.size() >= weaksOrder.size()) return true;
        
    }
    if(set.size() >= weaksOrder.size()) return true;
    else return false;
}

bool friendsOrder(int depth, vector <int> friends, int mid, int n, vector<int> &weak, vector<int> &dist, uint bit){ 
    if(depth == mid){
        for(int start=0; start<weak.size(); start++){
            vector <int> weaksOrder;
            for(int next= start; next<weak.size()+start; next++){
                weaksOrder.push_back(weak[next%weak.size()]);
            }
            if(friends.size() >= weaksOrder.size()) return true;
            
            bool res = calc(false, n, friends, weaksOrder);
            if(res) return true;
            reverse(weaksOrder.begin(), weaksOrder.end());
            res = calc(true, n, friends, weaksOrder);
            if(res) return true;        
        }
        return false;
    }
    bool res = false;
    for(int i=0; i<mid; i++){
        if(bit & (1<<i)) continue;
        friends[depth] = dist[i];
        res = friendsOrder(depth + 1, friends, mid, n, weak, dist, bit|(1<<i));  
        if(res) return true;
    }
    return res;
}

bool support(int mid, int n, vector<int> &weak, vector<int> &dist){
    
    uint bit = 0;
    vector<int> friends(mid);
    return friendsOrder(0, friends, mid, n, weak, dist, bit);
}

void binarySearch(int &answer, int n, vector<int> &weak, vector<int> &dist){
    int left = 1, right = dist.size();
    while(left <= right){
        int mid = (right-left)/2 + left;  
        if(support(mid, n, weak, dist)){
            right = mid-1;
            answer = (answer > mid ? mid: answer);
        }else{
            left = mid+1;
        }
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    if(n <= 2) return 1;
    
    int answer = 2147483647;
    sort(dist.begin(), dist.end(), cmp);
    if(n <= dist[0]) return 1;
    binarySearch(answer, n, weak, dist);
    
    return (answer == 2147483647 ? -1 : answer);
}
```

# ~~Code 1~~

```cpp
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;
vector <int> gap;
bool cmp(const int &a, const int &b){
    return a>b;
}
void setGap(int n, vector<int> &weak, vector<int> &dist){
    for(int i=1; i<weak.size(); i++) gap.push_back(weak[i]-weak[i-1]+1);
    if(weak.size() >= 2) gap.push_back(weak[0]+n - weak[weak.size()-1] + 1);
}
bool support(int mid, int n, vector<int> &weak, vector<int> &dist){
    if(weak.size() <= mid) return true;
    int nowTotalCoverLength = 0, distTotal1 = 0, distTotal2 = 0;
    for(int i=0; i<mid; i++) nowTotalCoverLength += dist[i];
    
    if(gap.size() %2 == 1){
        for(int i=1; i<gap.size(); i+=2) distTotal1 += gap[i];
        distTotal1 = min(distTotal1+gap[0], distTotal1+gap[gap.size()-1]);
        //distTotal1--;
    }else{
        for(int i=0; i<gap.size(); i++){
            if(i%2==0) distTotal1+=gap[i];
            else distTotal2+=gap[i];
        }
        distTotal1 = min(distTotal1, distTotal2);
    }
    cout << nowTotalCoverLength <<' '<<distTotal1<<'\n';
    return distTotal1 < nowTotalCoverLength; 
}

int binarySearch(int n, vector<int> &weak, vector<int> &dist){
    int left = 1, right = dist.size(), answer=-1;
    while(left <= right){
        //투입 인원
        int mid = (right-left)/2 + left;  
        cout << "인원 : "<<mid<<'\n';
        if(support(mid, n, weak, dist)){
            //가능하면 투입인원 줄여
            right = mid-1;
            answer = mid;
        }else{
            left = mid+1;
        }
    }
    return answer;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    if(weak.size() < 2) return 1;
    int answer = 0;
    sort(dist.begin(), dist.end(), cmp);
    setGap(n, weak, dist);
    for(int i=0; i<gap.size(); i++) cout << gap[i]<<' ';
    cout << '\n';
    answer = binarySearch(n, weak, dist);
    
    return answer;
}
```