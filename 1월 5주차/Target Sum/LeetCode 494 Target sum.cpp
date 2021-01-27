#define ll long long
class Solution {
public:
    int answer;

    void search(int cur, vector<int>& nums, ll sum) {
        if (cur == nums.size() - 1) {
            if (sum == 0) {
                answer++;
            }
            return;
        }
        search(cur + 1, nums, sum - nums[cur + 1]);
        search(cur + 1, nums, sum + nums[cur + 1]);
    }

    int findTargetSumWays(vector<int>& nums, int S) {
        answer = 0;
        search(-1, nums, (ll)S);
        return answer;
    }
};