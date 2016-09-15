#include "std.hpp"

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        res.reserve(n);
        int curr = 1;
        while (res.size() != n) {
            res.emplace_back(curr);
            if (curr * 10 <= n) {
                // 1, 10, 100, 1000
                curr *= 10;
            } else if (curr % 10 < 9 && curr + 1 <= n) {
                // 1001, 1002, ... 1009
                curr += 1;
            } else {
                // drop 10 while last digits is '9'
                // 1, 10, 1000, 1001, 1002, 1003, 1004, 1005 -> 101
                // or
                // 2999 -> 3
                while ((curr / 10) % 10 == 9) {
                    curr /= 10;
                }
                curr = curr / 10 + 1;
            }
        }
        return res;
    }
};

void test_lexicalOrder()
{
    auto res = Solution().lexicalOrder(234);
}
