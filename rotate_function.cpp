#include "std.hpp"

// https://leetcode.com/problems/rotate-function/

// Example:
// A = [4, 3, 2, 6]
// F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
// F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
// F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
// F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

// f(0)   = 0 * a(0)   + 1 * a(1) + 2 * a(2) + ... + (n-1) * a(n-1)
// f(1)   = 0 * a(n-1) + 1 * a(0) + 2 * a(1) + ... + (n-1) * a(n-2)
// f(2)   = 0 * a(n-2) + 1 * a(n) + 2 * a(0) + ... + (n-1) * a(n-3)
// ...
// f(n-1) = 0 * a(1)   + 1 * a(2) + 2 * a(3) + ... + (n-1) * a(0)
//
// f(1) = f(0)   + a(0) + a(1) + ... + a(n-1) - n * a(n-1)
// f(2) = f(1)   + a(0) + a(1) + ... + a(n-1) - n * a(n-2)
// f(i) = f(i-1) + a(0) + a(1) + ... + a(n-1) - n * a(n-i)

class Solution {
public:
    int maxRotateFunction(const vector<int>& A) {
        const size_t n = A.size();
        if (n == 0) return 0;
        int res = 0;
        int elementsSum = A[0];
        for (size_t j = 1; j < n; ++j) {
            res += j * A[j];
            elementsSum += A[j];
        }
        int sum = res;
        for (size_t i = 1; i < n; ++i)
        {
            sum += elementsSum;
            sum -= A[n-i] * n;
            if (sum > res)
                res = sum;
        }
        return res;
    }
};

void test_maxRotateFunction()
{
    assert(0 == Solution().maxRotateFunction({}));
    assert(26 == Solution().maxRotateFunction({4,3,2,6}));
}
