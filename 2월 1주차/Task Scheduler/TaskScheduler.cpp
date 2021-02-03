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