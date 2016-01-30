#include "std.hpp"

// https://leetcode.com/problems/gray-code/

class Solution {
public:
    void recur(int n, bitset<32> & tmp, vector<int> & res)
    {
        if (n == 0)
        {
            res.emplace_back(static_cast<int>(tmp.to_ulong()));
            return;
        }

        recur(n - 1, tmp, res);
        tmp.flip(n - 1);
        recur(n - 1, tmp, res);
    }
    vector<int> grayCode(int n)
    {
        vector<int> res;
        bitset<32> tmp;
        recur(n, tmp, res);
        return res;
    }
};

void test_grayCode()
{
}
