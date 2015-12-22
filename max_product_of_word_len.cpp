#include "std.hpp"

// https://leetcode.com/problems/maximum-product-of-word-lengths/

class Solution {
public:
    int maxProduct(vector<string> & words)
    {
        using TMask = uint32_t;

        size_t const n = words.size();

        vector<TMask> masks(n, 0);
        for (size_t i = 0; i < n; ++i)
        {
            TMask & mask = masks[i];
            for (auto const & c : words[i]) mask |= 1 << (c - 'a'); // 26 bits
        }

        size_t res = 0;
        for (size_t i = 0; i < n; ++i)
        {
            size_t maxl = 0;
            for (size_t j = i + 1; j < n; ++j)
            {
                if ((masks[i] & masks[j]) == 0 && words[j].size() > maxl)
                {
                    size_t t = words[i].size() * words[j].size();
                    if (t > res)
                    {
                        maxl = words[j].size();
                        res = t;
                    }
                }
            }
        }
        return res;
    }
};

void test_maxProductOfWordLen()
{
    vector<string> v = {"fffffef","eabffebeb","dfadee","aecccafff","cbdbbecbfad","fdefdecccfc",
    "abebcaca","ee","eecdedfee","bdd","dedfef","ffebccf","cae","aeab","fcabfeeeaaf",
    "dfcd","fafb","ccedfc","ce","cb","ba","ebeedaa","aebabca","cddaebabcf","abee","efbcababbef",
    "abfdc","afedabcbfdb","ebfebcef","fcecf","cdfecabf","adc","efabaf","dffdbbdedfe","dcfe","ecb",
    "cfbfbfcad","bdddefcd","bbccffedcca","dbddd","abbdbf","daffb","eddadbeaed","dccfebacf","efdfac",
    "eedcde","dfacadafda","bbef","cdefb","cffeaa","adbb","acbedfedfd","abcadbbb","daeadbffcdf",
    "caeefbbff","bbcbfafdab","dfebeacadb","faaeec","ffce","ddfcbe","ac","ecdbeddcb","fe","ecbbefaced",
    "ccfdda","eddabb","aaadccefade","ddcb","dec","abbbeafdccf","aefeadedcf","cfaeddeff","edbeadafe",
    "feeff","edbaba","aeeafaec","dedebffca","bfdaaec","becafc","bfae","adadefbbebf","cfaeccccc",
    "affdfbebccd","cacde","eeed","fcdbfeefbb","dbadcdfbaae","fbca","bfbffd","fefaeabe","cdecadbd",
    "ecabbcbdd","feededad","dbdaccaeaaa","ef","badddc","eee","aabeaebdddb","abceae","faebdf","bbceea"};
    Solution().maxProduct(v);
}
