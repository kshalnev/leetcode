#include "std.hpp"

// https://leetcode.com/problems/counting-bits/

class Solution {
public:
    vector<int> countBits(int num)
    {
        // bits(100100) = bits(10010) + 0
        // bits(100101) = bits(10010) + 1
        // or
        // bits(i) = bits(i>>1) + (i&1);

        vector<int> bits(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};

void test_countingBits()
{
    auto res = Solution().countBits(5);
    assert(res == vector<int>({0,1,1,2,1,2}));
}
