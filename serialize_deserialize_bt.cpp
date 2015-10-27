#include "std.hpp"

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
    TreeNode* alloc_node(int val)
    {
        return new TreeNode(val);
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        if (nullptr == root)
            return "null";

        string res;
        size_t nullcnt = 0;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode* r = q.front();
            q.pop();

            if (nullptr == r) ++nullcnt;
            else
            {
                for (size_t i = 0; i < nullcnt; ++i)
                    res += "null,";
                nullcnt = 0;
                res += to_string(r->val) + ",";
                q.push(r->left);
                q.push(r->right);
            }
        }

        if (!res.empty()) res.pop_back();
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return nullptr;
    }
};

void test_SerializeDeserializeBT()
{
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(-1);
    root->right->left = new TreeNode(2);
    root->right->left->left = new TreeNode(9);

    Codec codec;
    string data = codec.serialize(root);
    codec.deserialize(data);
}
