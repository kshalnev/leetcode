#include "std.hpp"

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/ but for BST

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
    template <typename F> static void pre_order(TreeNode* root, F&& f)
    {
        f(root->val);
        if (nullptr != root->left) pre_order(root->left, f);
        if (nullptr != root->right) pre_order(root->right, f);
    }

    template <typename F> static void in_order(TreeNode* root, F&& f)
    {
        if (nullptr != root->left) in_order(root->left, f);
        f(root->val);
        if (nullptr != root->right) in_order(root->right, f);
    }

    class Functor
    {
    public:
        void operator()(int val)
        {
            m_value += to_string(val);
            m_value += ",";
        }
        string & get_ref()
        {
            if (!m_value.empty() && m_value.back() == ',')  m_value.pop_back();
            return m_value;
        }
    private:
        string m_value;
    };

    static vector<int> read(string s)
    {
        vector<int> res;
        size_t pos = 0;
        while (pos != string::npos)
        {
            const size_t d = s.find(',', pos);
            string::iterator e = s.end();
            size_t newpos = string::npos;
            if (d != string::npos)
            {
                e = s.begin() + d;
                newpos = d + 1;
            }
            int val = stoi(string(s.begin() + pos, e));
            res.push_back(val);
            pos = newpos;
        }
        return res;
    }

    TreeNode* alloc_node(int val)
    {
        return new TreeNode(val);
    }

    using TVectorIntConstIterator = vector<int>::const_iterator;

    TreeNode* restore(const TVectorIntConstIterator& pre_b,
                      const TVectorIntConstIterator& pre_e,
                      const TVectorIntConstIterator& in_b,
                      const TVectorIntConstIterator& in_e)
    {
        if (pre_b == pre_e || in_b == in_e) return nullptr;

        const auto in_root = find(in_b, in_e, *pre_b);
        if (in_root == in_e) return nullptr;

        const auto sub_left_in_b = in_b;
        const auto sub_left_in_e = in_root;
        const auto sub_right_in_b = in_root + 1;
        const auto sub_right_in_e = in_e;

        const size_t left_size = distance(sub_left_in_b, sub_left_in_e);

        TreeNode* root = alloc_node(*pre_b);
        root->right = restore(pre_b + left_size + 1, pre_e, sub_right_in_b, sub_right_in_e);
        root->left = restore(pre_b + 1, pre_b + left_size + 1, sub_left_in_b, sub_left_in_e);

        return root;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (nullptr == root) return string();
        Functor pre_f, in_f;
        pre_order(root, pre_f);
        in_order(root, in_f);
        string res;
        res.reserve(pre_f.get_ref().size() + 1 + in_f.get_ref().size());
        res += pre_f.get_ref();
        res += ";";
        res += in_f.get_ref();
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        size_t pos = data.find(';');
        if (pos == string::npos) return nullptr;
        vector<int> pre_v = read(string(data.begin(), data.begin() + pos));
        vector<int> in_v = read(string(data.begin() + pos + 1, data.end()));
        if (pre_v.size() != in_v.size() || pre_v.empty()) return nullptr;
        return restore(pre_v.begin(), pre_v.end(), in_v.begin(), in_v.end());
    }
};

void test_SerializeDeserializeBinTree()
{
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(1);

    Codec codec;
    codec.deserialize(codec.serialize(root));
}
