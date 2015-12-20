#include "std.hpp"

// https://leetcode.com/problems/remove-duplicate-letters/

class Solution {
public:
    string removeDuplicateLetters(string s)
    {
        if (s.empty())
            return s;

        unsigned int cnt[26] = {0};
        for (auto const c : s) cnt[c-'a'] += 1;

        size_t pos = 0;
        for (size_t i = 0; i < s.length(); ++i)
        {
            if (s[i] < s[pos])
                pos = i;
            if (0 == --cnt[s[i]-'a'])
                break;
        }

        string r = s.substr(pos + 1);
        r.erase(remove_if(r.begin(), r.end(), [&](char c){ return c == s[pos]; }), r.end());

        return s[pos] + removeDuplicateLetters(r);
    }
};

void test_removeDuplicateLetters()
{
    string s = Solution().removeDuplicateLetters("cbacdcbc");
    assert(s == "acdb");

    s = Solution().removeDuplicateLetters("bcabc");
    assert(s == "abc");
}
