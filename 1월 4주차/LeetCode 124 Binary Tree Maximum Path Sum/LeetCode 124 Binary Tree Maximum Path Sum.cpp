#include <algorithm>
#define minimum -2147483648
class Solution {
public:
    int maximum;
    int dfs(TreeNode* now) {

        int mid = now->val;
        int midLeft = (now->left ? dfs(now->left) + mid : -2147483648);
        int midRight = (now->right ? dfs(now->right) + mid : -2147483648);
        int midLeftRight = (now->left && now->right ? midLeft + midRight - mid : -2147483648);

        int currentMax = max(midLeftRight, max(mid, max(midLeft, midRight)));
        maximum = (maximum < currentMax ? currentMax : maximum);

        if (currentMax == midLeftRight) return max(midLeft, midRight);
        return currentMax;
    }

    int maxPathSum(TreeNode* root) {
        maximum = root->val;
        dfs(root);
        return maximum;
    }
};