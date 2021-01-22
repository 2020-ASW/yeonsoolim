#include <algorithm>
#define minimum -2147483648
class Solution {
public:
    int maximum;
    int dfs(TreeNode* now) {
        int total = 0;

        int left = 0, midLeft = 0;
        int right = 0, midRight = 0;
        int midLeftRight = 0;
        int mid = now->val;
        if (now->left) {
            left = dfs(now->left);
            midLeft = left + mid;
        }
        else {
            left = -2147483648;
            midLeft = -2147483648;
        }

        if (now->right) {
            right = dfs(now->right);
            midRight = right + mid;
        }
        else {
            right = -2147483648;
            midRight = -2147483648;
        }

        if (now->left && now->right) {
            midLeftRight = left + mid + right;
        }
        else {
            midLeftRight = -2147483648;
        }

        int currentMax = max(midLeftRight, max(mid, max(left, max(midLeft, max(right, midRight)))));
        maximum = (maximum < currentMax ? currentMax : maximum);
        if (currentMax == mid || currentMax == midRight || currentMax == midLeft) {
            return currentMax;
        }
        else if (currentMax == midLeftRight) {
            return max(midLeft, midRight);
        }
        else {
            return max(currentMax + mid, mid);
        }
    }

    int maxPathSum(TreeNode* root) {
        maximum = root->val;
        dfs(root);
        return maximum;
    }
};