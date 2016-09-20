#include "std.hpp"

// https://leetcode.com/problems/random-pick-index/

class Solution {
public:
    vector<int> nums_;

    Solution(vector<int> nums)
    : nums_(move(nums))
    {
    }

    int pick(int target)
    {
        int c = 0;
        int i = 0;
        int r = -1;
        for (int n : nums_) {
            if (n == target) {
                ++c;
                if (rand() % c == 0) {
                    r = i;
                }
            }
            ++i;
        }
        return r;
    }
};
