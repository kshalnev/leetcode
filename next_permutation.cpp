#include "std.hpp"

// https://leetcode.com/problems/next-permutation/

class Solution {
public:
    void nextPermutation(vector<int>& nums)
    {
        const size_t n = nums.size();

        if (n <= 1)
            return;

        if (n == 2 || is_sorted(nums.rbegin(), nums.rend())) {
            reverse(nums.begin(), nums.end());
            return;
        }

        size_t t = 0;
        for (size_t i = nums.size()-2;; --i) {
            if (i == 0 || nums[i] < nums[i+1]) {
                t = i;
                break;
            }
        }

        size_t m = 0;
        for (size_t i = nums.size()-1;i>t; --i) {
            if (nums[i] > nums[t]) {
                m = i;
                break;
            }
        }

        swap(nums[t], nums[m]);
        reverse(nums.begin() + t + 1, nums.end());
    }
};

void test_nextPermutation()
{
    vector<int> v1 = {1,2,3,4};
    Solution().nextPermutation(v1);

    vector<int> v2 = {4,3,2,1};
    Solution().nextPermutation(v2);

    vector<int> v3 = {1,3,2,4};
    Solution().nextPermutation(v3);

    vector<int> v4 = {1,3,4,2};
    Solution().nextPermutation(v4);
}
