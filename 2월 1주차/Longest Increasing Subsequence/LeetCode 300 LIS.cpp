class Solution {
public:
    vector <int> lis;

    int binarySearch(int x) {
        int left = 0, right = lis.size();
        int idx = 0;
        while (left <= right) {
            int mid = (right - left) / 2 + left;

            if (lis[mid] == x) {
                return mid;
            }
            else if (lis[mid] < x) {
                left = mid + 1;
            }
            else if (lis[mid] > x) {
                right = mid - 1;
                idx = mid;
            }
        }
        return idx;
    }

    int lengthOfLIS(vector<int>& nums) {
        lis.push_back(-100000);
        for (int i = 0; i < nums.size(); i++) {
            int now = nums[i];
            if (lis[lis.size() - 1] < now) {
                lis.push_back(now);
            }
            else if (lis[lis.size() - 1] > now) {
                lis[binarySearch(now)] = now;
            }

        }
        for (int i = 0; i < nums.size(); i++) {
            cout << lis[i] << ' ';
        }
        return lis.size() - 1;

    }
};