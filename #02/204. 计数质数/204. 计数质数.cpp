#if defined(LocalLymphV)
#include "../../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
统计所有小于非负整数 n 的质数的数量。

 

示例 1：

输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
示例 2：

输入：n = 0
输出：0
示例 3：

输入：n = 1
输出：0
 

提示：

0 <= n <= 5 * 106

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-primes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///76ms 76.14% 22.1M 5.03%
    using vi = vector<int>;

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vi nums(n, 0);
        vi primes;
        for (int i = 3; i < n; i += 2)
        {
            if (!nums[i]) primes.emplace_back(i);
            for (int p : primes)
            {
                int t = p * i;
                if (n <= t) break;
                nums[t] = p;
                if (p == nums[i]) break;
            }
        }
        return primes.size() + 1;
    }
};

class SolutionV5 {///100ms 73.42% 12.4M 14.72%
    using vc = vector<char>;
    using vi = vector<int>;

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vc nums(n, 0);
        vi primes;
        for (int i = 3; i < n; i += 2)
        {
            if (!nums[i]) primes.emplace_back(i);
            for (int p : primes)
            {
                int t = p * i;
                if (n <= t) break;
                nums[t] = 1;
                if (!(p % i)) break;
            }
        }
        return primes.size() + 1;
    }
};

class SolutionV4 {///80ms 75.83% 12.4M 14.78%
    using vc = vector<char>;
    using vi = vector<int>;

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vc nums(n, 0);
        vi primes;
        for (int i = 3; i < n; i += 2)
        {
            if (!nums[i]) primes.emplace_back(i);
            for (int p : primes)
            {
                int t = p * i;
                if (t < n) nums[t] = 1;
                else break;
            }
        }
        return primes.size() + 1;
    }
};


class SolutionV3 {///96ms 73.76% 10.7M 16.43%
    using vc = vector<char>;
    using vi = vector<int>;

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vc nums(n / 2, 0);
        vi primes;
        for (int i = 3; i < n; i += 2)
        {
            if (!nums[(i - 3) / 2]) primes.emplace_back(i);
            for (int p : primes)
                if (p * i < n) nums[(p * i - 3) / 2] = 1;
                else break;
        }
        return primes.size() + 1;
    }
};

class SolutionV2 {///164ms 70.60% 9.2M 19.51%
    using vb = vector<bool>;
    using vi = vector<int>;

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vb nums(n / 2, 0);
        vi primes;
        for (int i = 3; i < n; i += 2)
        {
            if (!nums[(i - 3) / 2]) primes.emplace_back(i);
            for (int p : primes)
                if (p * i < n) nums[(p * i - 3) / 2] = 1;
                else break;
        }
        return primes.size() + 1;
    }
};


class SolutionV1 {///TLE
    using vb = vector<bool>;
    using vi = vector<int>;

    bool isPrime (int x, vi & primes)
    {
        for (int y : primes) if (!(x % y)) return 0;
        return 1;
    }

public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vi primes;
        for (int i = 3; i < n; i += 2)
            if (isPrime(i, primes)) primes.emplace_back(i);
        return primes.size() + 1;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<int> xs{
        10, 50, 100
    };
    for (auto x : xs)
        print(x), print(Solution().countPrimes(x)), print("===");
    return 0;
}
#endif
