#include "std.hpp"

namespace
{

struct TreeNode
{
    TreeNode * left;
    TreeNode * right;
    int val;
    TreeNode(int v) : left(nullptr), right(nullptr), val(v) {}
};

class Solution
{
public:
    class bst_reverse_iterator
    {
    public:
        bst_reverse_iterator() = default;
        bst_reverse_iterator(bst_reverse_iterator const &) = default;
        bst_reverse_iterator & operator=(bst_reverse_iterator const &) = default;
        bst_reverse_iterator(bst_reverse_iterator &&) = default;
        bst_reverse_iterator & operator=(bst_reverse_iterator &&) = default;

        bst_reverse_iterator(TreeNode * root)
        {
            init(root);
        }
        TreeNode * get() const
        {
            return m_s.empty() ? nullptr : m_s.top();
        }
        bool valid() const
        {
            return !m_s.empty();
        }
        void move()
        {
            if (m_s.empty())
                return;

            TreeNode * t = m_s.top();
            m_s.pop();

            if (t->left)
                init(t->left);
        }

    private:
        void init(TreeNode * root)
        {
            while (nullptr != root)
            {
                m_s.push(root);
                root = root->right;
            }
        }

        stack<TreeNode*, vector<TreeNode*>> m_s;
    };

    TreeNode * findReverseKth(TreeNode * root, size_t k)
    {
        bst_reverse_iterator itr(root);
        for (size_t i = 0; i < k; ++i)
        {
            if (!itr.valid())
                break;
            itr.move();
        }
        return itr.get();
    }
};

} // namespace

void test_FindReverseBstKth1()
{
    TreeNode * root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(5);
    root->left->left->left = new TreeNode(1);
    root->right = new TreeNode(9);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(11);

    assert(Solution().findReverseKth(root, 7)->val == 1);
    assert(Solution().findReverseKth(root, 3)->val == 7);
    assert(Solution().findReverseKth(root, 1)->val == 9);
    assert(Solution().findReverseKth(root, 8) == nullptr);
}
