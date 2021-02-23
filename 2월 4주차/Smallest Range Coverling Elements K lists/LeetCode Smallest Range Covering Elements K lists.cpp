class Solution {
public:
    vector <pair<int,int> > all;
    vector <int> kind;

    void mergeAll(vector<vector<int>> &nums){
        for(int i=0; i<nums.size(); i++){
            for(auto &num : nums[i]){
                all.push_back({num, i+1});
            }
        }
        sort(all.begin(), all.end());
    }

    bool check(bitset <3502> &bit, int left, int right){
        if(bit.count() == kind.size()-1) return true;
        return false;
    }

    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> answer;
        pair<int,int> resultPair;
        int resultSize = 2147483647;

        kind.resize(nums.size()+1);
        mergeAll(nums);
        bitset <3502> bit;
        int left = 0, right = 0;
        bit.set(all[left].second);
        kind[all[left].second]++;

        while(left < all.size()){
            if(check(bit, left, right)){
                int lv = all[left].first;
                int rv = all[right].first;
                int diff = abs(rv-lv)+1;

                if(resultSize > diff){
                    resultPair = {lv, rv};
                    resultSize = diff;
                    if(diff == 1) break;
                }

                kind[all[left].second]--;
                if(kind[all[left].second] == 0) bit.reset(all[left].second);
                left++;
            }else{
                right++;
                if(right>=all.size()) break;
                kind[all[right].second]++;
                if(kind[all[right].second] == 1) bit.set(all[right].second);
            }
            if(left>right) break;
            if(right>=all.size())break;
        }
        answer.push_back(resultPair.first);
        answer.push_back(resultPair.second);
        return answer;
    }
};