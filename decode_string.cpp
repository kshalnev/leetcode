#include "std.hpp"

// https://leetcode.com/problems/decode-string/

class Solution {
private:
    static std::string::iterator findEnd(
        std::string::iterator i, std::string::iterator iend)
    {
        for (int l = 1; i != iend; ++i)
        {
            if (*i == '[')
                ++l;
            else if (*i == ']') {
                if ((--l) == 0)
                    break;
            }
        }
        return i;
    }
public:
    string decodeString(string s)
    {
        ostringstream o;
        auto i = s.begin(), iend = s.end();
        for (int k = 0; i != iend; ++i)
        {
            if (isdigit(*i)) {
                k = k * 10 + *i - '0';
            } else if (*i == '[') {
                auto e = findEnd(i + 1, iend);
                string t = decodeString(string(i + 1, e));
                for (; k > 0; --k) {
                    o << t;
                }
                i = e;
            } else {
                o << *i;
            }
        }

        return o.str();
    }
};

void test_decodeString()
{
    assert(Solution().decodeString("3[a]2[bc]") == "aaabcbc");
    assert(Solution().decodeString("3[a2[c]]") == "accaccacc");
}
