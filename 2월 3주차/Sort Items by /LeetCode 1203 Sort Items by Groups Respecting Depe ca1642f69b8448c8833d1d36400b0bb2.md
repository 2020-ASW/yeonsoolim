# LeetCode 1203 Sort Items by Groups Respecting Dependencies

# sort

# Pre

- **문제 :**

    There are n items each belonging to zero or one of m groups where `group[i]` is the group that the `i`-th item belongs to and it's equal to -1 if the `i`-th item belongs to no group. 
    **⇒ i 번째 항목이 속해있는 그룹[i]  but, 속해있지 않으면 그룹[i] = -1**

    The items and the groups are zero indexed. 
    A group can have no item belonging to it.
    **⇒ items 과 groups는 0부터 indexing.
    ⇒ group은 item외에는 원소가 없다.**

- **반환 :**

    Return a sorted list of the items such that:

    - The items that belong to the same group are next to each other in the sorted list.
    ⇒ 같은 그룹에 있는 아이템들은 연속 되어야 한다.
    - There are some relations between these items where `beforeItems[i]` is a list containing all the items that should come before the `i`th item in the sorted array (to the left of the `i`th item).
    ⇒ `beforeItems`의 원소는 그 전에 미리 모든 items를 포함 되어야 한다.

    Return any solution if there is more than one solution and return an **empty list** if there is no solution.
    ⇒ 여러개 정답이 있으면 그 중 아무거나 한 개.
    ⇒ 하나도 정답이 없다면 empty list.

# Solve

해야 할 것 : 

- cycle 조사
- item들의 순서
- group들의 순서

1. group 번호가 -1인 item들은 -1 group이 아니라 개인인 것이다.
2. item별로 tpsort를 한다.
3. group별로 tpsort를 한다.
4. tpsort된 item들을 group별로 모아준다.
5. tpsort된 group순서대로 item들을 배열한다.

1. group 번호가 -1인 item들은 -1 group이 아니라 개인인 것이다.

    ```java
    for(int item=0; item<n; item++){
        if(group[item] == -1){
            groupInfo.resize(extendM+1);
            group[item] = extendM++;
        }
    }
    ```

2. item별로 tpsort를 한다.
3. group별로 tpsort를 한다.

    ```java
    void tpSort(vector <int> &sorted, vector <unordered_set<int> > &info){
            indegree.clear();
            indegree.resize(info.size());

            for(auto &i : info){
                for(auto iter=i.begin(); iter!=i.end(); ++iter){
                    indegree[*iter]++;
                }
            }
            
            queue <int> q;
            for(int i=0; i<info.size(); i++){
                if(indegree[i] == 0) q.push(i);
            }
            while(!q.empty()){
                int curr = q.front(); q.pop();
                sorted.push_back(curr);
                for(auto &next : info[curr]){
                    indegree[next] -= 1;
                    if(indegree[next] == 0) q.push(next);
                }
            }
        }
    ```

    **3 - 1 cycle 찾기**

    ```java
    tpSort(sortedItem, itemInfo);
    if(sortedItem.size() != N) return answer;
    tpSort(sortedGroup, groupInfo);
    if(sortedGroup.size() != extendM) return answer;
    ```

4. tpsort된 item들을 group별로 모아준다.

    ```java
    for(auto &item: sortedItem){
        v[group[item]].push_back(item);
    }
    ```

5. tpsort된 group순서대로 item들을 배열한다.

    ```java
    for(auto &group : sortedGroup){
        for(auto iter= v[group].begin(); iter!=v[group].end(); ++iter){
            answer.push_back(*iter);
        }
    }
    ```

# Code

```java
class Solution {
private:
    int N;
    int M;
    int extendM;
    vector <unordered_set<int> > groupInfo;
    vector <unordered_set<int> > itemInfo;
    vector <int> indegree;
public:
    
    void init(int &n, int &m, vector<int>& group, vector<vector<int>>& beforeItems){
        this->N = n;
        this->M = m;
        this->extendM = m;
        itemInfo.resize(n);
        groupInfo.resize(m);
        for(int item=0; item<n; item++){
            if(group[item] == -1){
                groupInfo.resize(extendM+1);
                group[item] = extendM++;
            }
        }
        
        for(int item=0; item<n; item++){
            for(auto &before : beforeItems[item]){
                itemInfo[before].insert(item);
                if(group[item] != group[before]){
                    
                    groupInfo[group[before]].insert(group[item]);
                }
            }
        }
    }
    
    void tpSort(vector <int> &sorted, vector <unordered_set<int> > &info){
        indegree.clear();
        indegree.resize(info.size());

        for(auto &i : info){
            for(auto iter=i.begin(); iter!=i.end(); ++iter){
                indegree[*iter]++;
            }
        }
        
        queue <int> q;
        for(int i=0; i<info.size(); i++){
            if(indegree[i] == 0) q.push(i);
        }
        
        while(!q.empty()){
            int curr = q.front(); q.pop();
            sorted.push_back(curr);
            for(auto &next : info[curr]){
                indegree[next] -= 1;
                if(indegree[next] == 0) q.push(next);
            }
        }
    }
    
    
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        init(n, m, group, beforeItems);
        
        vector <int> sortedItem;
        vector <int> sortedGroup;
        vector<int> answer;
        
        tpSort(sortedItem, itemInfo);
        if(sortedItem.size() != N) return answer;
        tpSort(sortedGroup, groupInfo);
        if(sortedGroup.size() != extendM) return answer;
        
        
        vector <vector<int> > v(sortedGroup.size());
        
        for(auto &item: sortedItem){
            v[group[item]].push_back(item);
        }
        
        for(auto &group : sortedGroup){
            for(auto iter= v[group].begin(); iter!=v[group].end(); ++iter){
                answer.push_back(*iter);
            }
        }
        
        return answer;
    }
};
```