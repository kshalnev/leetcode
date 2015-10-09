#include "std.hpp"

// https://leetcode.com/problems/word-pattern/

class Solution {
public:
    bool wordPattern(string pattern, string str)
    {
      unordered_map<int, string> c2s;
      unordered_map<string, int> s2c;

      size_t i = 0;
      istringstream iss(str);
      for (; !iss.eof() && i < pattern.size(); ++i)
      {
          int c = pattern[i];
          string s;
          iss >> s;

          auto const itr_c2s = c2s.find(c);
          if (itr_c2s == c2s.end())
          {
              if (!s2c.emplace(s, c).second)
                  break;
              c2s.emplace(c, move(s));
          }
          else if (itr_c2s->second != s || s2c[s] != c)
            break;
      }

      return i == pattern.size() && iss.eof();
    }
};

void test_wordPattern()
{
  assert(true == Solution().wordPattern("abba", "dog cat cat dog"));
  assert(false == Solution().wordPattern("abba", "dog cat cat fish"));
  assert(false == Solution().wordPattern("aaaa", "dog cat cat dog"));
  assert(false == Solution().wordPattern("abba", "dog dog dog dog"));
}
