
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
    class bst_reverse_iterator
    {
    public:
        bst_reverse_iterator(bst_reverse_iterator const &) = default;
        bst_reverse_iterator & operator=(bst_reverse_iterator const &) = default;

        bst_reverse_iterator(TreeNode * root = nullptr)
            : m_p(root != nullptr ? get_bst_max(root) : nullptr)
        {
        }
        TreeNode * get() const
        {
            return m_p;
        }
        bst_reverse_iterator & operator++()
        {
            if (m_p != nullptr)
                m_p = get_bst_prev(m_p);
            return *this;
        }
        bool operator!=(bst_reverse_iterator const & itr) const
        {
            return m_p != itr.m_p;
        }

    private:
        static TreeNode * get_bst_max(TreeNode * root)
        {
            while (root->right != nullptr)
                root = root->right;
            return root;
        }
        static TreeNode * get_bst_min(TreeNode * root)
        {
            while (root->left != nullptr)
                root = root->left;
            return root;
        }
        static bool is_left_child(TreeNode * node)
        {
            return node->parent != nullptr && node->parent->left == node;
        }
        static TreeNode * get_bst_prev(TreeNode * node)
        {
            if (node->left != nullptr)
                return get_bst_max(node->left);
            while (is_left_child(node))
                node = node->parent;
            return node->parent;
        }

        TreeNode * m_p;
    };

    TreeNode * findReverseKth(TreeNode * root, size_t k)
    {
        bst_reverse_iterator itr(root), end;
        for (size_t i = 0; i < k && itr != end; ++i, ++itr) {}
        return itr.get();
    }
};

} // namespace

void test_FindReverseBstKth4()
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
