#include <algorithm>

class Solution {
public:
    
    deque <int> dq;
    vector <int> answer;

    void firstSetting(vector<int>& nums, int k){
        for(int i=0; i<k; i++){
            while(!dq.empty() && nums[dq.back()] < nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
        }
    }
    void print(){
        deque <int> ::iterator iter;
        for(iter=dq.begin(); iter!=dq.end(); ++iter){
            cout << *iter<<' ';
        }cout << '\n';
    }
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        firstSetting(nums, k);
        if(nums.size() == 1) return nums;
        
        for(int i=k; i<nums.size(); i++){
            answer.push_back(nums[dq.front()]);
            if(dq.front()+k == i){
                dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()] < nums[i]){   
                dq.pop_back();
            }
            dq.push_back(i);
        }
        answer.push_back(nums[dq.front()]);
        
        return answer;    
    }
    
};