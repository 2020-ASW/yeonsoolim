# LeetCode 621 Task Scheduler

# 문제이해

- CPU와 같이 작업을 하는 Scheduler가 있다.
- 같은 종류의 작업을 하기 위해서는 딜레이 n 만큼이 지나야 한다.
- 모든 작업을 끝내는데 걸리는 최소 시간을 구하라.

# Solve

- 작업의 종류는 대문자로 주어지기 때문에 26가지.

    ```cpp
    void initMap(vector<char>& tasks){
        for(int i=0; i<tasks.size(); i++){ 
            tasksV[tasks[i]-'A']++;
        }
        for(auto i=0; i<tasksV.size(); i++){
            if(tasksV[i] == 0) tasksV.erase(tasksV.begin()+(i--));
        }
    }
    ```

- 딜레이 n이 지난다면 아무 작업이나 올 수 있다.

    딜레이를 중점적으로 체크 할 수 있어야함.

    ```cpp
    while(remain){

        int cycle = n+1;
        sort(tasksV.begin(), tasksV.end(), cmp);
        while(cycle){
            for(auto iter = tasksV.begin(); iter!=tasksV.end(); ){
                (*iter)--;
                remain--;
                cycle--;
                
                if(*iter == 0) iter = tasksV.erase(iter);
                else ++iter;
                
                if(remain == 0) break;
                if(cycle == 0) break;
            }   
            if(remain == 0) break;
            if(cycle != 0) {
                answer+=cycle;
                break;
            }
        }
    }
    ```

# Code

```cpp
#include <vector>

class Solution {
public:
    
    vector <int> tasksV;
    Solution() : tasksV(26,0) {}
    bool static cmp(const int &a, const int &b){
        return a>b;
    }
    void initMap(vector<char>& tasks){
        for(int i=0; i<tasks.size(); i++){ 
            tasksV[tasks[i]-'A']++;
        }
        for(auto i=0; i<tasksV.size(); i++){
            if(tasksV[i] == 0) tasksV.erase(tasksV.begin()+(i--));
        }
    }
    int leastInterval(vector<char>& tasks, int n) {
        int remain = tasks.size(), answer = tasks.size();
        initMap(tasks);
        
        while(remain){

            int cycle = n+1;
            sort(tasksV.begin(), tasksV.end(), cmp);
            while(cycle){
                for(auto iter = tasksV.begin(); iter!=tasksV.end(); ){
                    (*iter)--;
                    remain--;
                    cycle--;
                    
                    if(*iter == 0) iter = tasksV.erase(iter);
                    else ++iter;
                    
                    if(remain == 0) break;
                    if(cycle == 0) break;
                }   
                if(remain == 0) break;
                if(cycle != 0) {
                    answer+=cycle;
                    break;
                }
            }
        }
        return answer;
    }
};
```

![LeetCode%20621%20Task%20Scheduler%200c1f602186874d6ea4f6d5448e25d219/Untitled.png](LeetCode%20621%20Task%20Scheduler%200c1f602186874d6ea4f6d5448e25d219/Untitled.png)