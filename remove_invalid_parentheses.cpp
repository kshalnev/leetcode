#include "std.hpp"

// https://leetcode.com/problems/remove-invalid-parentheses/

class Solution {
public:
    bool IsValidParentheses(string const & s)
    {
        int n = 0;
        for (auto const c : s)
        {
            if (c == '(') ++n;
            else if (c == ')')
            {
                --n;
                if (n < 0)
                    return false;
            }
        }
        return n == 0;
    }

    vector<string> removeInvalidParentheses(string s)
    {
        vector<string> res;

        if (s.empty() || IsValidParentheses(s))
        {
            res.emplace_back(move(s));
            return res;
        }

        queue<pair<int, string>> q;
        q.push(make_pair(0, s));

        unordered_set<string> checked;

        int minl = 0;

        while (!q.empty())
        {
            string t = q.front().second;
            int l = q.front().first;
            q.pop();

            if (l > minl && !res.empty())
                break;

            if (checked.find(t) != checked.end())
                continue;
            checked.insert(t);

            if (IsValidParentheses(t))
            {
                if (res.empty())
                {
                    res.emplace_back(move(t));
                    minl = l;
                }
                else if (minl == l)
                {
                    res.emplace_back(move(t));
                }
            }
            else
            {
                for (size_t i = 0; i < t.size(); ++i)
                {
                    if (t[i] ==  '(' || t[i] == ')')
                    {
                        string x = string(s.begin(), s.begin() + i) + t.substr(i + 1);
                        q.push(make_pair(l + 1, move(x)));
                    }
                }
            }
        }

        if (res.empty())
            res.emplace_back(string(""));

        return res;
    }
};

void test_removeInvalidParentheses()
{
    auto res = Solution().removeInvalidParentheses("()(((((((()");
    res = Solution().removeInvalidParentheses("()())()");
    res = Solution().removeInvalidParentheses("(a)())()");
    res = Solution().removeInvalidParentheses(")(");
}
