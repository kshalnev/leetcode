#include "std.hpp"

// https://leetcode.com/problems/wiggle-sort-ii/

class Solution {
public:
    void wiggleSort(vector<int> & nums)
    {
        // sorted array interleave
        // as
        // A0 A1 A2 A3 A4 A5
        // interleave as A2 A5 A1 A4 A0 A3
        // or
        // A0 A1 A2 A3 A4 A5 A6
        // interleave as A3 A6 A2 A5 A1 A4 A0
        //
        // where first index i goes down from (n + 1) / 2
        // and second index i goes down from n
        //
        // by using such apporoach we spit same elements in middle,
        // in example like 1, 3, 2, 2, 3, 1

        vector<int> tmp = nums;
        sort(tmp.begin(), tmp.end());
        int n = static_cast<int>(tmp.size());
        int i = (n + 1) / 2, j = n;
        for (int x = 0; x < n; ++x)
        {
            nums[x] = ((x & 1) == 0) ? tmp[--i] : tmp[--j];
        }
    }
};

void test_wiggleSort2()
{
    vector<int> nums1 = {1,5,1,1,6,4};
    Solution().wiggleSort(nums1);
    assert(vector<int>({1,6,1,5,1,4}) == nums1);

    vector<int> nums2 = {1,3,2,2,3,1};
    Solution().wiggleSort(nums2);
    assert(vector<int>({2,3,1,3,1,2}) == nums2);
}
