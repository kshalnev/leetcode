#include "std.hpp"

// https://leetcode.com/problems/longest-palindrome/

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> c2c;
        for (char c : s) {
            c2c[c] += 1;
        }
        int len = 0;
        int num_odd = 0;
        for (const auto& kv : c2c) {
            if (kv.second > 1) {
                len += (kv.second >> 1) << 1;
            }
            if (kv.second & 1) {
                ++num_odd;
            }
        }
        return len + ((num_odd > 0) ? 1 : 0);
    }
};
