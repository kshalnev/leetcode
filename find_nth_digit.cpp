#include "std.hpp"

// https://leetcode.com/problems/nth-digit/
// Inspired by https://discuss.leetcode.com/topic/59383/0ms-c-solution-with-detail-explanation/2

class Solution {
public:
    int findNthDigit(int N) {
        // 1-9 is 1 digits x 9
        // 10-99 is 2 digits x 100-10=90
        // 100-999 is 3 digits x 1000-100=900
        // 1000-9999 is 4 digits x 10000-1000=90000
        // etc.

        using LongInteger = long int;

        // 1. find how many digits in number X in position N
        // 2. find the number X, that corresponds to position N
        // 3. find the digit D in the number X, than corresponds to position N

        // 1. find how many digits in number X in position N
        LongInteger end = 10; // end, upper bound (not included)
        LongInteger digits_per_num = 1; // digits per number
        LongInteger count_digits = 9; // count of digits
        LongInteger p_count_digits = 0; // previous count of digits
        LongInteger p_end = 0; // previous end
        LongInteger p_digits_per_num = 0; // previous digits per num
        while (count_digits < N) {
            p_count_digits = count_digits;
            p_end = end;
            p_digits_per_num = digits_per_num;
            end *= 10;
            digits_per_num++;
            count_digits += p_end * 9 * digits_per_num;
        }

        if (digits_per_num == 1)
            return N;

        // 2. find the number X, that corresponds to position N
        LongInteger base = 1;
        for (LongInteger i = 1; i < digits_per_num; ++i)
            base *= 10;
        LongInteger N_in_base = N - p_count_digits;
        LongInteger value_index = N_in_base / digits_per_num;
        if (N_in_base % digits_per_num != 0)
            value_index++;
        LongInteger value = base + value_index - 1;

        // 3. find the digit D in the number X, than corresponds to position N
        // note 0 is most right digit
        LongInteger index_in_value = (digits_per_num - N_in_base % digits_per_num);
        if (index_in_value == digits_per_num)
            index_in_value = 0;
        for (LongInteger i = 0; i < index_in_value; ++i) {
            value /= 10;
        }
        int digit = value % 10;

        return digit;
    }
};

void test_findNthDigit()
{
    // 1-9 ( 9 )
    // 10-99 ( 90x2 + 9x1 = 189 )
    assert(5 == Solution().findNthDigit(121));

    assert(1 == Solution().findNthDigit(1));
    assert(5 == Solution().findNthDigit(5));
    assert(9 == Solution().findNthDigit(9));

    assert(1 == Solution().findNthDigit(10));
    assert(0 == Solution().findNthDigit(11));

    assert(1 == Solution().findNthDigit(12));
    assert(1 == Solution().findNthDigit(13));

    assert(1 == Solution().findNthDigit(14));
    assert(2 == Solution().findNthDigit(15));

    assert(1 == Solution().findNthDigit(16));
    assert(3 == Solution().findNthDigit(17));
}
