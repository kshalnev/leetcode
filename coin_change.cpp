#include "std.hpp"

// https://leetcode.com/problems/coin-change/

class Solution {
public:
    int coinChange(vector<int> const & coins, int amount) {
        int const MAX = amount + 1;
        vector<int> dp(amount + 1, MAX); // dp[i] - how coins is required for amount 'i'
        dp[0] = 0; // 0 coins is required for amount 0
        for (int a = 1; a <= amount; ++a)
        {
            for (int c : coins)
            {
                if (a >= c)
                {
                    dp[a] = min( dp[a], dp[a - c] + 1 );
                }
            }
        }
        return dp[amount] == MAX ? -1 : dp[amount];
    }
};

void test_coinChange()
{
    assert(2 == Solution().coinChange(vector<int>({1,2,3}), 6));
}
