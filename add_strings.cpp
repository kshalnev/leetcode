#include "std.hpp"

// https://leetcode.com/problems/add-strings/

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res;
        res.reserve(max(num1.length(), num2.length()) + 1);
        auto i1 = num1.rbegin(), i1end = num1.rend();
        auto i2 = num2.rbegin(), i2end = num2.rend();
        int prev = 0;
        for (; i1 != i1end && i2 != i2end; ++i1, ++i2) {
            int r = (*i1 - '0') + (*i2 - '0') + prev;
            if (r >= 10) {
                r -= 10;
                prev = 1;
            } else {
                prev = 0;
            }
            res.push_back(r + '0');
        }
        if (i1 == i1end) {
            i1 = i2, i1end = i2end;
        }
        for (; i1 != i1end; ++i1) {
            int r = (*i1 - '0') + prev;
            if (r >= 10) {
                r -= 10;
                prev = 1;
            } else {
                prev = 0;
            }
            res.push_back(r + '0');
        }
        if (prev != 0) {
            res.push_back('1');
        }
        reverse(res.begin(), res.end());
        return res;
    }
};


