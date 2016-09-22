#include "std.hpp"

// https://leetcode.com/problems/remove-k-digits/

class Solution {
public:
    string removeKdigits(string num, int k)
    {
        if (static_cast<int>(num.size()) <= k)
            return "0";

        size_t pi = 0; // peak index
        for (int i = 0; i < k; ++i)
        {
            // find first peak
            while ((pi + 1) < num.size() && num[pi+1] >= num[pi]) ++pi;

            // remove the first peak
            num.erase(num.begin() + pi);

            if (pi > 0) --pi;
        }

        auto ri = num.begin();
        for (; ri != num.end() && *ri == '0'; ++ri) {}
        if (ri == num.end()) return "0";
        if (ri == num.begin()) return num;
        else return string(ri, num.end());
    }
};
