#include "std.hpp"

// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

class Solution {
public:
    int findPath(vector<vector<int>> & matrix, size_t r, size_t c, vector<vector<int>> & dp)
    {
        if (dp[r][c] != 0)
            return dp[r][c];

        int const val = matrix[r][c];

        int subLen = 0;
        if (c > 0 && matrix[r][c - 1] > val)
            subLen = max(subLen, findPath(matrix, r, c - 1, dp));
        if (r > 0 && matrix[r - 1][c] > val)
            subLen = max(subLen, findPath(matrix, r - 1, c, dp));
        if (c < matrix[r].size() - 1 && matrix[r][c + 1] > val)
            subLen = max(subLen, findPath(matrix, r, c + 1, dp));
        if (r < matrix.size() - 1 && matrix[r + 1][c] > val)
            subLen = max(subLen, findPath(matrix, r + 1, c, dp));

        dp[r][c] = subLen + 1;
        return dp[r][c];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        size_t const rows = matrix.size();
        size_t const cols = rows == 0 ? 0 : matrix[0].size();

        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        int maxLen = 0;
        for (size_t r = 0; r < rows; ++r)
        {
            for (size_t c = 0; c < cols; ++c)
            {
                maxLen = max(maxLen, findPath(matrix, r, c, dp));
            }
        }

        return maxLen;
    }
};

void test_longestIncreasingPath()
{
    vector<vector<int>> matrix;
    matrix.emplace_back(vector<int>({9,9,4}));
    matrix.emplace_back(vector<int>({6,6,8}));
    matrix.emplace_back(vector<int>({2,1,1}));
    assert(4 == Solution().longestIncreasingPath(matrix));

    matrix.clear();
    matrix.emplace_back(vector<int>({3,4,5}));
    matrix.emplace_back(vector<int>({3,2,6}));
    matrix.emplace_back(vector<int>({2,2,1}));
    assert(4 == Solution().longestIncreasingPath(matrix));
}
