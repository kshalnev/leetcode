#include "std.hpp"

// https://leetcode.com/problems/anagrams/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> const & strs)
    {
        unordered_map<string, vector<string>> h;
        for (string const & str : strs)
        {
            string k = str;
            sort(k.begin(), k.end());
            h[k].push_back(str);
        }

        vector<vector<string>> res;
        res.reserve(h.size());
        for (auto & kv : h)
        {
            sort(kv.second.begin(), kv.second.end());
            res.emplace_back(move(kv.second));
        }

        return res;
    }
};

void test_groupAnagrams()
{
    auto res = Solution().groupAnagrams(vector<string>({""}));
}
