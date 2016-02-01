#include "std.hpp"

// https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

class Solution {
public:
    template <typename F>
    static bool parse(string const & str, F && f)
    {
        size_t pos = 0;
        string s;
        while (true)
        {
            size_t const end = str.find(',', pos);
            if (end == string::npos)
            {
                s.insert(s.end(), str.begin() + pos, str.end());
                if (!f(s)) return false;
                break;
            }
            else
            {
                s.insert(s.end(), str.begin() + pos, str.begin() + end);
                if (!f(s)) return false;
                pos = end + 1;
            }
            s.clear();
        }
        return true;
    }

    bool isValidSerialization(string const & preorder)
    {
        // special case which is treated as valid
        if (preorder == "#") return true;

        using Terminality = bool;
        bool constexpr kNonTerminal = false;
        bool constexpr kTerminal = true;

        stack<Terminality> s;

        bool res = parse(preorder, [&](string const & n)->bool
        {
            if (n != "#")
            {
                // O
                s.push(kNonTerminal);
                return true;
            }
            else
            {
                if (s.empty()) return false;
                if (s.top() == kNonTerminal)
                {
                    // O + # -> O,#
                    s.push(kTerminal);
                    return true;
                }
                else if (s.size() >= 2)
                {
                    // O,# + # -> O,#,# -> #
                    while (s.size() >= 2 && s.top() == kTerminal)
                    {
                        s.pop(); // pop a terminal node
                        if (s.empty() || s.top() == kTerminal) return false;
                        s.pop(); // pop a non terminal node
                    }
                    s.push(kTerminal);
                    return true;
                }
                return false;
            }
        });

        if (!res)
            return false;

        return s.size() == 1 && s.top() == kTerminal;
    }
};

void test_isValidSerialization()
{
    assert(true == Solution().isValidSerialization("#"));
    assert(true == Solution().isValidSerialization("1,#,#"));
    assert(true == Solution().isValidSerialization("1,0,#,#,#"));
    assert(true == Solution().isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    assert(false == Solution().isValidSerialization("1,#"));
    assert(false == Solution().isValidSerialization("9,#,#,1"));
}
