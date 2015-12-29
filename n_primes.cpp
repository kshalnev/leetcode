#include "std.hpp"

class Solution
{
private:
    bool IsPrime(int value, vector<int> const & primes)
    {
        for (size_t i = 2; i < primes.size(); ++i)
        {
            int const prime = primes[i];
            if (value % prime == 0) return false;
            if (prime * prime > value) break;
        }
        return true;
    }
public:
    vector<int> getNPrimes(size_t N)
    {
        vector<int> primes;
        primes.reserve(N);
        primes.push_back(1);
        primes.push_back(2);

        for (int i = 3; primes.size() <= N; i+=2)
        {
            if (IsPrime(i, primes))
            {
                primes.push_back(i);
            }
        }

        primes.resize(N);
        return primes;
    }
};

void test_getNPrimes()
{
    Solution().getNPrimes(0);
    Solution().getNPrimes(1);
    Solution().getNPrimes(2);
    Solution().getNPrimes(3);
    Solution().getNPrimes(10);
    Solution().getNPrimes(10000);
}
