#include "std.hpp"

// https://leetcode.com/problems/sum-of-left-leaves/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void dsf(TreeNode* root, TreeNode* parent, int& res) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr && parent != nullptr && parent->left == root) {
            res += root->val;
            return;
        }
        dsf(root->left, root, res);
        dsf(root->right, root, res);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        int res = 0;
        dsf(root, nullptr, res);
        return res;
    }
};
