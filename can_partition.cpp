#include "std.hpp"

// https://leetcode.com/contest/8/problems/partition-equal-subset-sum/

class Solution {
public:
    set<pair<int, int>> false_;
    bool recur(int summ, int curr, int index, const vector<int>& nums)
    {
        if (curr == summ) return true;
        if (curr > summ) return false;
        if (index >= nums.size()) return false;
        if (false_.find(make_pair(curr, index)) != false_.end()) return false;
        if (recur(summ, curr + nums[index], index + 1, nums)) return true;
        if (recur(summ, curr, index + 1, nums)) return true;
        false_.insert(make_pair(curr, index));
        return false;
    }
    bool canPartition(const vector<int>& nums) {
        const int summ = accumulate(nums.begin(), nums.end(), 0);
        if (summ & 1) return false; // summ is odd, partition is impossible
        return recur(summ / 2, 0, 0, nums);
    }
};

