#include "std.hpp"

// https://leetcode.com/problems/unique-binary-search-trees/

/*
 * See description here:
 * http://www.ideserve.co.in/learn/total-number-of-possible-binary-search-trees-with-n-keys
 * https://www.quora.com/Given-n-how-many-structurally-unique-BSTs-binary-search-trees-that-store-values-1-to-n-are-there
 *
 * num of BSTs with N keys = num of BSTs with '1' as root + num of BSTs with '2' as root + ... + num of BSTs with 'N' as root
 *
 * num of BSTs with 'i' as root:
 * with 'i' element as root, left subtree has i - 1 elements, and right subtree has N - i elements
 * num of BSTs with 'i' as root = num of BSTs with i - 1 keys * num of BSTs with N - i keys
 *
 *                            N
 * num of BST with N keys =  SUM  num of BSTs with i - 1 keys * num of BSTs with N - i keys
 *                          i = 1
 *
 * num of BSTs with 0 keys = 1
 * num of BSTs with 1 key = 1
 */

class Solution {
public:
    // recursive solution is
    /*
    int numTrees(int n)
    {
        if (n == 0 || n == 1) return 1;

        int res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int left = numTrees(i - 1);
            int right = numTrees(n - i);
            res += left * right;
        }

        return res;
    }
    */

    // dp solution
    int numTreesImpl(int n, vector<int> & dp)
    {
        if (dp[n] != -1) return dp[n];

        int res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int left = numTreesImpl(i - 1, dp);
            int right = numTreesImpl(n - i, dp);
            res += left * right;
        }

        dp[n] = res;
        return res;
    }

    int numTrees(int n)
    {
        if (n == 0 || n == 1) return 1;

        vector<int> dp(n + 1, -1);
        dp[0] = 1;
        dp[1] = 1;

        int res = numTreesImpl(n, dp);
        return res;
    }
};

void test_numTrees()
{
    assert(5 == Solution().numTrees(3));
}
