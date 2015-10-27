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

    template <typename F>
    void parse_list(const string& data, F&& f)
    {
        size_t level_limit = 1;
        size_t level_index = 0;
        size_t index_on_level = 0;
        size_t level_valid = 0;

        size_t pos = 0;
        while (pos != string::npos)
        {
            size_t d = data.find(',', pos);
            string::const_iterator e = data.end();
            size_t newpos = string::npos;
            if (d != string::npos)
            {
                e = data.begin() + d;
                newpos = d + 1;
            }
            string val(data.begin() + pos, e);
            if (val == "null")
            {
                f(nullptr, level_index, index_on_level);
            }
            else
            {
                const int n = stoi(val);
                f(&n, level_index, index_on_level);
                ++level_valid;
            }

            ++index_on_level;
            if (index_on_level == level_limit)
            {
                index_on_level = 0;
                level_limit *= 2;
                level_index += 1;
            }

            pos = newpos;
        }
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        if (nullptr == root)
            return "null";

        string res;
        size_t null_cnt = 0;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode* r = q.front();
            q.pop();

            if (nullptr == r) ++null_cnt;
            else
            {
                for (size_t i = 0; i < null_cnt; ++i)
                    res += "null,";
                null_cnt = 0;
                res += to_string(r->val) + ",";
                q.push(r->left);
                q.push(r->right);
            }
        }

        if (!res.empty()) res.pop_back();
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        if (data.empty()) return nullptr;

        TreeNode* root = nullptr;

        vector<TreeNode*> parent_level;
        vector<TreeNode*> curr_level;
        size_t prev_level_index = 0;
        parse_list(data, [&](const int* value, size_t level_index, size_t index_on_level)
        {
            if (level_index == 0)
            {
                if (value != nullptr)
                {
                    root = alloc_node(*value);
                    curr_level.push_back(root);
                }
                return;
            }

            if (root == nullptr) return;

            if (level_index != prev_level_index)
            {
                parent_level = move(curr_level);
                curr_level.clear();
                prev_level_index = level_index;
            }

            if (value != nullptr)
            {
                TreeNode* node = alloc_node(*value);
                curr_level.push_back(node);
                size_t parent_index = index_on_level / 2;
                if (index_on_level & 1)
                    parent_level[parent_index]->right = node;
                else
                    parent_level[parent_index]->left = node;
            }
        });
        return root;
    }
};

namespace
{
void test_Serialize_1()
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
    assert(data == "5,4,7,3,null,2,null,-1,null,9");

    codec.deserialize(data);
}

void test_Serialize_2()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    Codec codec;
    string data = codec.serialize(root);
    assert(data == "1,2,3");

    codec.deserialize(data);
}

void test_Serialize_3()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);

    Codec codec;
    string data = codec.serialize(root);
    assert(data == "1,2,null,3");

    codec.deserialize(data);
}

void test_Serialize_4()
{
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);

    Codec codec;
    string data = codec.serialize(root);
    assert(data == "1,null,2,null,3");
}

void test_Serialize_5()
{
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    Codec codec;
    string data = codec.serialize(root);
    assert(data == "1,null,2,3");
}

void test_Serialize_6()
{
    Codec codec;
    codec.deserialize("1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null");
}
}

void test_SerializeDeserializeBT()
{
    test_Serialize_1();
    test_Serialize_2();
    test_Serialize_3();
    test_Serialize_4();
    test_Serialize_5();
    test_Serialize_6();
}
