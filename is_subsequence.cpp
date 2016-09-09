#include "std.hpp"

// https://leetcode.com/problems/is-subsequence/

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (t.empty()) return s.empty();
        if (s.empty()) return true;
        const size_t sn = s.length();
        size_t si = 0;
        for (const auto& tc : t) {
            if (tc == s[si]) {
                if ((++si) == sn)
                    return true;
            }
        }
        return false;
    }
};

