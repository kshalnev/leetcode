#include "std.hpp"

// https://leetcode.com/problems/longest-increasing-subsequence/

class Solution {
public:
    int lengthOfLIS(const vector<int> & nums)
    {
        const size_t n = nums.size();
        if (n <= 1) return n;

        vector<int> t(n, 1);
        for (size_t i = 1; i < n; ++i)
        {
            for (size_t j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                    if (t[j] + 1 > t[i])
                        t[i] = t[j] + 1;
            }
        }

        int tt = t[0];
        for (size_t i = 1; i < n; ++i)
            if (tt < t[i])
                tt = t[i];

        return tt;
    }
};

void test_lengthOfLIS()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(4 == Solution().lengthOfLIS(nums));
}
