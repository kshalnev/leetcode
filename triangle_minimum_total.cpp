#include "std.hpp"

// https://leetcode.com/problems/triangle/

// Top down DP solution
class Solution1 {
public:
    vector<unordered_map<int, int>> dp_;

    int recur(const vector<vector<int>>& triangle, size_t row_index, size_t col_index)
    {
        if (row_index == triangle.size()-1)
            return triangle[row_index][col_index];

        auto& um = dp_[row_index];
        auto itr = um.find(col_index);
        if (itr != um.end()) return itr->second;

        const vector<int>& row = triangle[row_index];
        const int left = recur(triangle, row_index + 1, col_index);
        const int right = recur(triangle, row_index + 1, col_index + 1);
        const int res = row[col_index] + min(left, right);

        um[col_index] = res;

        return res;
    }
    int minimumTotal(const vector<vector<int>>& triangle)
    {
        if (triangle.empty()) return 0;
        dp_.resize(triangle.size()-1);
        return recur(triangle, 0, 0);
    }
};

// Bottom up DP solution
class Solution2 {
public:
    int minimumTotal(const vector<vector<int>>& triangle)
    {
        if (triangle.empty()) return 0;

        vector<int> dp(triangle[triangle.size()-1]);
        for (size_t i = triangle.size()-1; i > 0; --i)
        {
            const vector<int>& row = triangle[i-1];
            for (size_t j = 0, jn = row.size(); j < jn; ++j)
            {
                dp[j] = min(dp[j], dp[j+1]) + row[j];
            }
        }

        return dp[0];
    }
};

void test_minimumTotal()
{
    vector<vector<int>> triangle = {{1},{2,3},{4,5,6}};
    assert(7 == Solution1().minimumTotal(triangle));
    assert(7 == Solution2().minimumTotal(triangle));
}

