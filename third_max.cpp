#include "std.hpp"

// https://leetcode.com/problems/third-maximum-number/

class Solution {
public:
    int thirdMax(const vector<int>& nums) {
        if (nums.empty()) return 0;
        int buff[3] = {0}; // buffer of max
        int buffLen = 0; // length of buffer (can be 1...3)
        for (int value : nums) {
            if (buffLen < 3) {
                buff[buffLen] = value;
                ++buffLen;
                if (buffLen == 3) {
                    sort(buff, buff + buffLen, [](int a, int b) { return !(a < b); });
                }
                continue;
            }
            if (value == buff[0] || value == buff[1] || value == buff[2]) {
                // we need only unique numbers, therefore skip value if it equals
                // to any in buffer of max
                continue;
            }
            if (value > buff[0]) {
                buff[2] = buff[1];
                buff[1] = buff[0];
                buff[0] = value;
            }
            else if (value > buff[1]) {
                buff[2] = buff[1];
                buff[1] = value;
            }
            else if (value > buff[2]) {
                buff[2] = value;
            }
        }
        if (buffLen != 3) {
            return *max_element(buff, buff + buffLen);
        }
        return buff[2];
    }
};
