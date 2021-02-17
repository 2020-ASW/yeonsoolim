# 매출 하락 최소화

[코딩테스트 연습 - 매출 하락 최소화](https://programmers.co.kr/learn/courses/30/lessons/72416)

### **문제 설명**

유통전문회사 `카카오상사` 의 오너인 `제이지` 는 새로운 사업 아이템을 구상하기 위해 전문경영인(CEO)인 `프로도`

에게 회사의 경영을 부탁하였습니다.

카카오상사는 직원들을 여러 개의 팀 단위로 조직을 구성하고 있으며 아래 그림은 CEO를 포함하여 10명의 직원과 4개의 팀으로 구성되어 있는 회사 조직도를 보여주고 있습니다.

![https://grepp-programmers.s3.ap-northeast-2.amazonaws.com/files/production/a55bfc1d-951e-478f-bbe8-f5eb021e5a0d/2021_kakao_sales_01.png](https://grepp-programmers.s3.ap-northeast-2.amazonaws.com/files/production/a55bfc1d-951e-478f-bbe8-f5eb021e5a0d/2021_kakao_sales_01.png)

그림의 조직도는 다음과 같이 설명할 수 있습니다.

1. 그림의 각 원들은 각각의 직원 1명을 표시하고 있으며, CEO를 포함하여 총 10명의 직원을 표시하고 있습니다.
2. 원 안에 적힌 두 개의 숫자는 직원의 정보를 담고 있습니다. 왼쪽 숫자는 `직원번호`이며 직원을 식별할 수 있도록 1번부터 순서대로 발급되는 일련번호이며, 오른쪽 숫자는 `해당 직원의 하루평균 매출액`을 나타냅니다. 위 그림에서 `1번` 직원은 14원을, `9번` 직원은 28원의 하루평균 매출액을 기록하고 있습니다.
3. CEO를 포함하여 모든 직원은 팀장 또는 팀원이라는 직위를 가지고 있으며 그림에서는 팀장과 팀원의 관계를 화살표로 표시하고 있습니다. 화살표가 시작되는 쪽의 직원은 팀장, 화살표를 받는 쪽의 직원은 팀원을 의미합니다.3-1. 직원번호 `1번`은 회사의 CEO로 고정되어 있으며, CEO는 항상 팀장이고 팀원일 수 없어 화살표를 받는 쪽이 될 수 없습니다.3-2. 반면에 CEO를 제외한 나머지 모든 직원들은 다른 누군가로부터 정확히 1개의 화살표를 받게 됩니다.3-3. 한 직원은 최대 2개의 팀에 소속될 수 있습니다. 만약 어떤 직원이 두 개의 팀에 소속되어 있다면, 반드시 하나의 팀에서는 팀장, 나머지 팀에서는 팀원이어야 합니다. 팀장을 겸임하거나, 두 개의 팀에서 팀원이 될 수는 없습니다. 예를들어 `10번` 직원은 `D팀`의 팀장이면서 동시에 `5번` 직원이 팀장으로 있는 `C팀`에 속한 팀원입니다.3-4. `5번, 9번, 10번` 직원은 받는 쪽의 화살표와 시작하는 화살표가 모두 있으므로 팀장인 동시에 팀원입니다.3-5. `2번, 3번, 4번, 6번, 7번, 8번` 직원은 시작하는 화살표가 없고 받는 쪽의 화살표만 있으므로 팀장이 아니며 오직 팀원입니다.3-6. `1번` 직원인 CEO는 받는 쪽의 화살표가 없고 시작하는 화살표만 있으며 항상 팀원이 아닌 팀장입니다.3-7. 그림의 조직도에는 `A, B, C, D` 총 4개의 팀이 존재하며, 각각 `1번, 9번, 5번, 10번` 직원이 팀장 직위를 담당하게 됩니다.

제이지는 자신이 구상한 새로운 사업 아이템에 대해 직원들에게 설명하고자 하루 일정으로 워크숍을 계획하고 있습니다. 단, 모든 직원을 참석시킬 수 없어 아래와 같은 기준으로 워크숍에 참석할 직원들을 선발하려고 합니다.

1. 워크숍에서 교육받은 내용은 전 직원들에게 공유되어야 하므로 `모든 팀은 최소 1명 이상`의 직원을 워크숍에 참석시켜야 합니다.
2. 워크숍 기간 동안, 회사의 매출 손실을 최소화하는 것이 중요하므로 워크숍에 참석하는 직원들의 하루평균 매출액의 합이 최소가 되어야 합니다.

위 그림의 조직도에서 회색으로 색칠된 `1번, 7번, 10번` 직원을 워크숍에 참석시키면 모든 팀에서 최소 한 명 이상의 직원을 참석시킨 것이 되며, 해당 직원들의 하루평균 매출액의 합은 `44(14+13+17)원` 입니다. `10번 직원은 C팀과 D팀 모두에 속해 있으므로, 두 팀에서 모두 참석한 것으로 인정됩니다.`

### **[문제]**

직원들의 하루평균 매출액 값을 담은 배열 sales, 직원들의 `팀장-팀원`의 관계를 나타내는 2차원 배열 links가 매개변수로 주어집니다. 이때, 모든 팀에서 최소 한 명 이상 워크숍에 참석하면서, 참석하는 직원들의 하루평균 매출액의 합을 최소로 하려고 합니다. 그렇게 최소화된 매출액의 합을 구해서 return 하도록 solution 함수를 완성해 주세요.

### **[제한사항]**

- sales 배열의 크기는 2 이상 300,000 이하입니다. sales 배열의 크기는 CEO를 포함한 전체 직원 수와 같습니다.
    - sales 배열은 각 직원들의 하루평균 매출액을 담고 있으며, `1번` 직원부터 직원번호 순서대로 주어집니다.
    - sales 배열의 각 원소의 값은 0 이상 10,000 이하인 정수입니다.
- links 배열의 크기는 `sales 배열의 크기 - 1` 입니다. 즉, 전체 직원 수보다 1이 작습니다.
- links 배열의 각 원소는 [a, b] 형식입니다.
    - a는 팀장의 직원번호, b는 a팀장이 관리하는 팀원의 직원번호이며, a와 b는 서로 다른 자연수입니다.
    - 1 ≤ `a` ≤ `sales 배열의 크기` 입니다.
    - 2 ≤ `b` ≤ `sales 배열의 크기` 입니다.
    - 직원번호 1은 CEO로 정해져 있고 CEO는 항상 팀장으므로 b ≠ 1 입니다.
    - links 배열로 만들어지는 조직도는 하나의 트리 구조 형태입니다.
- 정답으로 return 되는 값은 2 - 1 이하인 자연수임이 보장됩니다.

# Solve

1. sales배열과 links배열을 통해 Tree구조를 만들어 준다.
2. Tree 구조를 탐색 할건데, 부하의 정보를 활용하기 위해서 BottomUp 방식 DP를 활용한다.
3. Bottom-Up이므로 모든 직원 & 모든 팀의 최소 비용은 CEO인 DP[1]에 있을 것이다.

## Tree 구조 setting

```cpp
struct Person{
    int cost;
    int boss;
    int idx;
};

unordered_map <int, vector<Person>> boss;
unordered_map <int, int> underling;

void treeSetting(vector <int> &sales, vector <vector<int> > &links){
    boss[0].push_back({0, 0, 1});  //cost 0 boss 0  CEO
    for(auto &link : links){
        boss[link[0]].push_back({sales[link[1]-1], link[0], link[1]});
        underling[link[1]] = link[0];
    }
    totalTeam = boss.size();
}
```

- 사실 풀고난 후에 생각해보면 Tree안에 이렇게 많은 구조 & 복잡한 구조 가 필요 없을 것 같다.

    → Optimize 가능하다.

## 탐색 중인 Node 현재 직원 & 팀이라 했을 때

해야 할 것 : 

1. **다음 탐색을 한다.**
    1. **부하가 있다면 부하 탐색 후 DP정보를 활용할 수 있도록 한다.**
    2. **부하가 없다면 ( Leaf Node ) 정보를 저장한 후 종료 한다.**
2. **팀원 모두에게 전파 할 수 있게 해야 한다.**
    1. **팀장이 참석 하면?**

        → 팀원은 참석해도 되고 참석 하지 않아도 된다.

    2. **팀장이 불참 하면?**

        → 팀원 중 적어도 1명은 참석해서 팀원에게 알려주어야 한다.

1. 다음 탐색을 한다.
    1. 부하가 있다면 부하 탐색 후 DP정보를 활용할 수 있도록 한다.
        - `boss[idx]`  : idx가 팀장인 팀에서 팀원의 정보가 들어있는 vector
    2. 부하가 없다면 ( Leaf Node ) 정보를 저장한 후 종료 한다.
        - `boss.find()` : boss map에 정보가 없다는 것은 팀원일뿐 팀장은 아니라는 것. ⇒ Leaf Node이다.

            → sales 배열을 이용하여 정보를 저장해 준다.
            참석 : `dp[idx][1] = sales[idx-1];` 
            불참 : `dp[idx][0] = 0;`

    ```cpp
    void search(vector <int> &sales, int idx){
        if(boss.find(idx) == boss.end()){ 
            dp[idx][1] = sales[idx-1];
            dp[idx][0] = 0;
            return;
        }

        for(auto &next : boss[idx]){
            search(sales, next.idx);
        }
    		...
    ```

2. 팀원 모두에게 전파 할 수 있게 해야 한다.
    1. 팀장이 참석 하면?

        **→ 팀원은 참석해도 되고 참석 하지 않아도 된다.**

        - `sum += min()`  :  idx가 팀장인 팀 에서 모든 팀원을 돌면서 그 팀원이 참석 or 불참 한 정보 중 최소값을 가지고 온다.
        - `dp[idx][1] = sum + sales[idx-1]`  :  idx (현재 node)가 참여하므로 현재 Node의 비용을 더해주어야 한다.

        ```cpp
        int sum = 0;
            for(int i=0; i<boss[idx].size(); i++){
          
                sum+=min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
        				...
            }
        dp[idx][1] = sum + sales[idx-1];
        ```

    2. 팀장이 불참 하면?

        → **팀원 중 적어도 1명은 참석해서 팀원에게 알려주어야 한다.**

        팀원 중 1명 ?

        - 명확한 경우  :  참석한 경우 [1]이 불참한 경우 [0] 보다 클 경우

            → 참석했으면 그 아래 team도 커버할 수 있으므로 아주 유리하다.

            `sum+=min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1])`  :  모든 팀원의 비용을 산정해 본다.
            `if(dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0])  pick = true;`  :  sum에 대한 정보를 알 수 있다.

            **이때 sum ⇒  sum에는 아주 유리한 팀원이 이미 들어가 있다.**

            `if(pick) dp[idx][0] = sum;`

        - 명확하지 않은 경우  :  팀원 모두 참여하지 않았을 때 최소가 나와서 강제로 지명해주어야 한다.

            → 가장 이득이 되는 팀원을 골라 주어야 한다.

            `diff = min(diff, dp[boss[idx][i].idx][1]-dp[boss[idx][i].idx][0]);`  :  명확한 경우는 참석한 경우 < 불참한 경우 이지만,  만족하지 않으므로,  가장 이득인 (차가 작은 경우) 팀원을 선택한다.

            **이때 sum ⇒ sum에는 모두 불참한 팀원들만 있다.**

            `else dp[idx][0] = diff + sum;`

        ```cpp
         bool pick = false;
            int diff= 987654321;
            int sum = 0;
        		for(int i=0; i<boss[idx].size(); i++){
                sum+=min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
                if(dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
                    pick = true;
                }
                diff = min(diff, dp[boss[idx][i].idx][1]-dp[boss[idx][i].idx][0]);
            }
        if(pick) dp[idx][0] = sum;
        else dp[idx][0] = diff + sum;
        ```

# Dirty Code  (pass)

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
struct Person{
    int cost;
    int boss;
    int idx;
};
int totalTeam;
int dp[300001][2];
unordered_map <int, vector<Person>> boss;
unordered_map <int, int> underling;
void treeSetting(vector <int> &sales, vector <vector<int> > &links){
    boss[0].push_back({0, 0, 1});  //cost 0 boss 0  CEO
    for(auto &link : links){
        boss[link[0]].push_back({sales[link[1]-1], link[0], link[1]});
        underling[link[1]] = link[0];
    }
    totalTeam = boss.size();
}

void search(vector <int> &sales, int idx){
    if(boss.find(idx) == boss.end()){  // leaf Node
       // cout << "\"" <<idx<<"\"" <<' '<<sales[idx-1]<<'\n';
        dp[idx][1] = sales[idx-1];
        dp[idx][0] = 0;
        return;
    }
    for(auto &next : boss[idx]){
        search(sales, next.idx);// 안방문
    }
    //0일때 -> 자식만 2팀 커버 가능.
    
    //dp[idx][1] = min(dp[boss[idx][0].idx][0], dp[boss[idx][0].idx][1]);
    //dp[idx][0] = dp[boss[idx][0].idx][1];
    
    bool pick = false;
    int diff= 987654321;
    int sum = 0;
    //int diff = dp[boss[idx][0].idx][1]-dp[boss[idx][0].idx][0];
   // cout << dp[idx][0]<<" "<<boss[idx].size()<<' ' <<fromUnderling<<'\n';
    for(int i=0; i<boss[idx].size(); i++){
        //dp[idx][1] = min(dp[idx][1], min(dp[idx][1]+dp[boss[idx][i].idx][0], dp[idx][1]+dp[boss[idx][i].idx][1]));
        sum+=min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
        //dp[idx][1] += min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
      //  dp[idx][0] += min(dp[idx][0], dp[boss[idx][i].idx][1]);
        //if(dp[boss[idx][i].idx][1] != 0 && dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
        //     pick = true;
        // }
        if(dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
            pick = true;
        }
        diff = min(diff, dp[boss[idx][i].idx][1]-dp[boss[idx][i].idx][0]);
        
        //dp[idx][0] += dp[boss[idx][i].idx][1];
    }
    if(pick) dp[idx][0] = sum;
    else dp[idx][0] = diff + sum;
    
    dp[idx][1] = sum + sales[idx-1];

   // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';

    //dp[idx][1] += fromUnderling;
    //dp[idx][0] = fromUnderling == 0 ? dp[idx][0] : fromUnderling;
   // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';
}
void print(int curr){
    for(auto &next : boss[curr]){
        cout << next.idx <<" : "<<dp[next.idx][0]<<' '<<dp[next.idx][1]<<'\n';
        print(next.idx);
    }
}
int solution(vector<int> sales, vector<vector<int>> links) {
    treeSetting(sales, links);
    search(sales, 0);

    //int curr = 1;
    //print(1);
    
   // cout << dp[0][0]<<','<<dp[0][1]<<'\n';
   // cout << dp[1][0]<<','<<dp[1][1]<<'\n';
    return min(dp[1][0], dp[1][1]);
}
```

# Dirty Code (Fail)

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
struct Person{
    int cost;
    int boss;
    int idx;
};
int totalTeam;
int dp[300001][2];
unordered_map <int, vector<Person>> boss;
unordered_map <int, int> underling;
void treeSetting(vector <int> &sales, vector <vector<int> > &links){
    boss[0].push_back({0, 0, 1});  //cost 0 boss 0  CEO
    for(auto &link : links){
        boss[link[0]].push_back({sales[link[1]-1], link[0], link[1]});
        underling[link[1]] = link[0];
    }
    totalTeam = boss.size();
}

void search(vector <int> &sales, int idx){
    if(boss.find(idx) == boss.end()){  // leaf Node
       // cout << "\"" <<idx<<"\"" <<' '<<sales[idx-1]<<'\n';
        dp[idx][1] = sales[idx-1];
        dp[idx][0] = 0;
        return;
    }
    for(auto &next : boss[idx]){
        search(sales, next.idx);// 안방문
    }
    //0일때 -> 자식만 2팀 커버 가능.
    
    dp[idx][1] = min(dp[boss[idx][0].idx][0], dp[boss[idx][0].idx][1]);
    //dp[idx][0] = dp[boss[idx][0].idx][1];
    
    bool pick = false;
    int diff = min(987654321,dp[boss[idx][0].idx][1]-dp[boss[idx][0].idx][0]);
   // cout << dp[idx][0]<<" "<<boss[idx].size()<<' ' <<fromUnderling<<'\n';
    for(int i=1; i<boss[idx].size(); i++){
        //dp[idx][1] = min(dp[idx][1], min(dp[idx][1]+dp[boss[idx][i].idx][0], dp[idx][1]+dp[boss[idx][i].idx][1]));
        dp[idx][1] += min(dp[boss[idx][i].idx][0], dp[boss[idx][i].idx][1]);
      //  dp[idx][0] += min(dp[idx][0], dp[boss[idx][i].idx][1]);
        //if(dp[boss[idx][i].idx][1] != 0 && dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
        //     pick = true;
        // }
        if(dp[boss[idx][i].idx][1] <= dp[boss[idx][i].idx][0]){
            pick = true;
        }
        diff = min(diff, dp[boss[idx][i].idx][1]-dp[boss[idx][i].idx][0]);
        
        //dp[idx][0] += dp[boss[idx][i].idx][1];
    }
    if(pick) dp[idx][0] = dp[idx][1];
    else dp[idx][0] = diff + dp[idx][1];
    
    dp[idx][1] += sales[idx-1];

   // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';

    //dp[idx][1] += fromUnderling;
    //dp[idx][0] = fromUnderling == 0 ? dp[idx][0] : fromUnderling;
   // cout << "idx : "<<idx<<' '<<dp[idx][0]<<','<<dp[idx][1]<<'\n';
}
void print(int curr){
    for(auto &next : boss[curr]){
        cout << next.idx <<" : "<<dp[next.idx][0]<<' '<<dp[next.idx][1]<<'\n';
        print(next.idx);
    }
}
int solution(vector<int> sales, vector<vector<int>> links) {
    treeSetting(sales, links);
    search(sales, 0);

    //int curr = 1;
    //print(1);
    
   // cout << dp[0][0]<<','<<dp[0][1]<<'\n';
   // cout << dp[1][0]<<','<<dp[1][1]<<'\n';
    return min(dp[1][0], dp[1][1]);
}
```