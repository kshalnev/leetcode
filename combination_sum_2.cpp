#include "std.hpp"

// https://leetcode.com/problems/combination-sum-ii/

class Solution {
public:
    void recur(const vector<int> & candidates, int target, size_t begin,
               vector<int> & subset,
               vector<vector<int>> & res)
    {
        if (0 == target)
        {
            res.push_back(subset);
            return;
        }
        const size_t n = candidates.size();
        for (size_t i = begin; i < n;)
        {
            if (candidates[i] > target)
                break;
            subset.push_back(candidates[i]);
            recur(candidates, target - candidates[i], i + 1, subset, res);
            subset.pop_back();
            ++i;
            while (i < n && candidates[i-1] == candidates[i]) ++i;
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> subset;
        recur(candidates, target, 0, subset, res);
        return res;
    }
};

void test_combinationSum2()
{
    vector<int> v = {10,1,2,7,6,1,5};
    Solution().combinationSum2(v, 8);
}
