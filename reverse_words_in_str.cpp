#include "std.hpp"

// https://leetcode.com/problems/reverse-words-in-a-string/

class Solution {
public:
    void reverseWords(string &s) {
        // reverse words in string
        reverse(s.begin(), s.end());
        for (string::iterator i = s.begin(); i != s.end();)
        {
            auto j = find_if(i, s.end(), [](int c)->bool{ return c == ' '; });
            reverse(i, j);
            if (j != s.end()) i = j + 1; else i = s.end();
        }

        // remove leading and trailing spaces
        // keep only one space between words
        string::iterator r = s.begin(), w = s.begin();
        bool has_space = true;
        for (; r != s.end(); ++r)
        {
            if (*r != ' ')
            {
                if (has_space)
                {
                    has_space = false;
                    if (w != s.begin())
                    {
                        *w = ' ';
                        ++w;
                    }
                }
                *w = *r;
                ++w;
            }
            else
                has_space = true;
        }
        s.erase(w, s.end());
    }
};

void test_reverseWordsInString()
{
    string s = " one   two   three   ";
    Solution().reverseWords(s);
    assert(s == "three two one");
}
