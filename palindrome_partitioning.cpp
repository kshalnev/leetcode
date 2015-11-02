#include "std.hpp"

// https://leetcode.com/problems/palindrome-partitioning/

class Solution {
public:
    static bool isPalindrome(string const & s)
    {
        const size_t n = s.length();
        if (n == 0) return false;
        for (size_t i = 0, j = n-1; i < j; ++i, --j)
            if (s[i] != s[j]) return false;
        return true;
    }
    static void recur(string const & s, size_t idx,
                    vector<string>& tmp, vector<vector<string>>& res)
    {
        const size_t n = s.length();
        if (idx == n)
        {
            res.emplace_back(tmp);
            return;
        }
        for (size_t i = idx; i < n; ++i)
        {
            string t(s.begin() + idx, s.begin() + i + 1);
            if (isPalindrome(t))
            {
                tmp.emplace_back(move(t));
                recur(s, i + 1, tmp, res);
                tmp.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        recur(s, 0, tmp, res);
        return res;
    }
};

void testPalidromePartitioning()
{
    Solution().partition("aab");
}
