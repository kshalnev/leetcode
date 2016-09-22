#include "std.hpp"

// https://leetcode.com/problems/count-and-say/

class Solution {
public:
    string countAndSay(int n) {
        // 1
        // one 1 = 11
        // two 1 = 21
        // one 2 one 1 = 1211
        // one 1 one 2 two 1 = 111221
        // three 1 two 2 one 1 = 312211
        string res = "1";
        string tmp;
        for (int i = 1; i < n; ++i) {
            tmp.clear();
            char pch = res[0];
            int count = 0;
            for (char ch : res) {
                if (ch == pch) {
                    ++count;
                } else {
                    tmp += to_string(count) + pch;
                    pch = ch;
                    count = 1;
                }
            }
            if (count > 0) {
                tmp += to_string(count) + pch;
            }
            res.swap(tmp);
        }
        return res;
    }
};
