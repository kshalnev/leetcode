#include "std.hpp"

namespace
{

struct TreeNode
{
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
    int val;
    TreeNode(int v) : left(nullptr), right(nullptr), parent(nullptr), val(v) {}
};

class Solution
{
public:
    static TreeNode * get_most_right(TreeNode * root)
    {
        while (nullptr != root->right) root = root->right;
        return root;
    }

    static bool is_left_child(TreeNode * node)
    {
        return node->parent != nullptr && node->parent->left == node;
    }

    static void recur(TreeNode * p, size_t & i, size_t k, TreeNode ** res)
    {
        // visit(p, i)

        if (i == k)
        {
            *res = p;
            return;
        }

        ++i;

        if (p->left != nullptr)
        {
            TreeNode * mr = get_most_right(p->left);
            recur(mr, i, k, res);

            if (*res != nullptr)
                return;
        }

        if (is_left_child(p))
            return;

        if (p->parent != nullptr)
        {
            recur(p->parent, i, k, res);
        }
    }

    TreeNode * findReverseKth(TreeNode * root, size_t k)
    {
        TreeNode * res = nullptr;
        TreeNode * mr = get_most_right(root);
        size_t i = 0;
        recur(mr, i, k, &res);
        return res;
    }
};

} // namespace

void test_FindReverseBstKth2()
{
    TreeNode * root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->left->parent = root;
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(5);
    root->left->left->parent = root->left;
    root->left->right->parent = root->left;
    root->left->left->left = new TreeNode(1);
    root->left->left->left->parent = root->left->left;
    root->right = new TreeNode(9);
    root->right->parent = root;
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(11);
    root->right->left->parent = root->right;
    root->right->right->parent = root->right;

    assert(Solution().findReverseKth(root, 7)->val == 1);
    assert(Solution().findReverseKth(root, 3)->val == 7);
    assert(Solution().findReverseKth(root, 1)->val == 9);
    assert(Solution().findReverseKth(root, 8) == nullptr);
}
