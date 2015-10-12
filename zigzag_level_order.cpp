#include "std.hpp"

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (nullptr == root)
            return res;
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));
        vector<int> row;
        int rowid = 0;
        while (!q.empty())
        {
            auto a = q.front();
            q.pop();
            if (rowid != a.second)
            {
                if (rowid & 1)
                    reverse(row.begin(), row.end());
                res.emplace_back(move(row));
            }
            row.push_back(a.first->val);
            rowid = a.second;
            if (nullptr != a.first->left)
                q.push(make_pair(a.first->left, a.second + 1));
            if (nullptr != a.first->right)
                q.push(make_pair(a.first->right, a.second + 1));
        }
        if (!row.empty())
        {
            if (rowid & 1)
                reverse(row.begin(), row.end());
            res.emplace_back(move(row));
        }
        return res;
    }
};
