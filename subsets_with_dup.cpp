#include "std.hpp"

// https://leetcode.com/problems/subsets-ii/

class Solution {
public:
    void recur(vector<int> const & nums, vector<int> & subset, size_t begin, vector<vector<int>> & res)
    {
        res.emplace_back(subset);
        size_t const n = nums.size();
        for (size_t i = begin; i < n;)
        {
            subset.push_back(nums[i]);
            recur(nums, subset, i + 1, res);
            subset.pop_back();
            ++i;
            while (i < n && nums[i] == nums[i-1]) ++i;
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int> & nums)
    {
        vector<vector<int>> res;
        vector<int> subset;
        sort(nums.begin(), nums.end());
        recur(nums, subset, 0, res);
        return res;
    }
};

void test_subsetsWithDup()
{
    vector<int> v({1,2,2,3});
    auto res = Solution().subsetsWithDup(v);
}
