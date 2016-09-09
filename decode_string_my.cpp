#include "std.hpp"

// Similar to
// https://leetcode.com/problems/decode-string/
// but format is:
// <num><text><num><text>

class Solution {
public:
    string decodeStringMy(string s) {
        ostringstream o;
        const auto iend = s.end();
        auto p = iend;
        int k = 0, len = 0;
        for (auto i = s.begin(); i != iend; ++i)
        {
            if (isdigit(*i))
            {
                if (len > 0)
                {
                    for (int i = 0; i < k; ++i) {
                        auto b = p;
                        auto e = p + len;
                        for (; b < e; ++b) o << *b;
                    }
                    k = 0;
                    len = 0;
                    p = iend;
                }
                k = k * 10 + (*i - '0');
            }
            else
            {
                if (len == 0)
                    p = i;
                ++len;
            }
        }
        if (len > 0)
        {
            for (int i = 0; i < k; ++i) {
                for (auto b = p; b < iend; ++b)
                    o << *b;
            }
        }
        return o.str();
    }
};

void test_decodeStringMy()
{
    string res = Solution().decodeStringMy("2ab3cd4e");
    assert(res == "ababcdcdcdeeee");

    res = Solution().decodeStringMy("12a4cd");
    assert(res == "aaaaaaaaaaaacdcdcdcd");
}
