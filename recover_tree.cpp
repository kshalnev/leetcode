#include "std.hpp"

// https://leetcode.com/problems/recover-binary-search-tree/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:    
    static void in_order(TreeNode * root, function<void(TreeNode *)> const & fn)
    {
        if (nullptr != root->left)
            in_order(root->left, fn);
        fn(root);
        if (nullptr != root->right)
            in_order(root->right, fn);
    }

    static bool is_bst(TreeNode * root)
    {
        function<bool(TreeNode *)> test;
        function<bool(TreeNode *)> * ptest = &test;
        TreeNode * prev = nullptr;
        test = [&](TreeNode * node)->bool
        {
            if (prev != nullptr)
            {
                if (prev->val > node->val)
                    return false;
            }
            prev = node;
            return true;
        };

        function<bool(TreeNode *)> dfs;
        function<bool(TreeNode *)> * pdfs = &dfs;
        dfs = [&](TreeNode * root)->bool
        {
            if (root->left)
            {
                if (!(*pdfs)(root->left))
                    return false;
            }
            if (!(*ptest)(root))
                return false;
            if (root->right)
            {
                if (!(*pdfs)(root->right))
                    return false;
            }
            return true;
        };

        return dfs(root);
    }

    void recoverTree(TreeNode* root)
    {
        if (root == nullptr)
            return;

        TreeNode * prev = nullptr;

        TreeNode * first = nullptr;
        TreeNode * second = nullptr;

        in_order(root, [&](TreeNode * node)
        {
            if (prev == nullptr)
            {
                prev = node;
                return;
            }

            if (node->val < prev->val)
            {
                if (nullptr == first)
                    first = prev;
                if (nullptr != first)
                    second = node;
            }

            prev = node;
        });

        if (first != nullptr && second != nullptr)
            swap(first->val, second->val);
    }
};

void test_recoverTree()
{
    TreeNode *r = new TreeNode(0);
    r->left = new TreeNode(1);

    assert(!Solution::is_bst(r));
    Solution().recoverTree(r);
    assert(Solution::is_bst(r));
}
