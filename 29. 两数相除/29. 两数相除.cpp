#if defined(LocalLymphV)
#include "../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

 

示例 1:

输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = truncate(3.33333..) = truncate(3) = 3
示例 2:

输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = truncate(-2.33333..) = -2
 

提示：

被除数和除数均为 32 位有符号整数。
除数不为 0。
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。本题中，如果除法结果溢出，则返回 231 − 1。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/divide-two-integers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 5.7M 62.09%
    using ll = long long;
    ll f (ll a, ll b)
    {
        if (!a) return 0;

        int sig = 1;
        if (a < 0) a = -a, sig = -sig;
        if (b < 0) b = -b, sig = -sig;

        ll rst = 0;

        for (int i = 31; 0 <= i; --i)
        if ((b << i) <= a)
        {
            rst += (ll(1) << i);
            a  -= (b << i);

        }
        return sig < 0 ? -rst : rst;
    }
public:
    int divide(int a, int b) {
        ll rst = f(a,b);
        return rst == int(rst) ? rst : INT_MAX;
    }
};

class SolutionV3 {///984ms 9.81% 6M 13.42%
public:
    int divide(int dividend, int divisor) {
        int a = dividend, b = divisor;
        if (!b) return 0;
        if (b == 1) return a;
        if (b == -1) return a == INT_MIN ? INT_MAX : -a;
        if (b == 2) return a >> 1;
        if (b == -2) return -(a >> 1);

        if (0 < a && 0 < b && a < b || a < 0 && b < 0 && b < a) return 0;
        if (0 < a && b < 0 && a + b < 0 || a < 0 && 0 < b && 0 < a + b) return 0;

        for (; !(b & 1); a >>=1, b >>= 1);

        int rst = 0;
        if (b == 1) return a;
        if (b == -1) return -a;
        int sig = 1;
        if (b < 0) b = -b, sig = -sig;
        if (a < 0)
        {
            for (; a <= 0; --rst)
                a += b;
            ++rst;
        }
        else
        {
            for (; 0 <= a; ++rst)
                a -= b;
            --rst;
        }

        return sig < 0 ? -rst : rst;
    }
};

///消2
class SolutionV2 {///908ms 9.81% 5.7M 81.14%
    using ll = long long;
    ll f (ll a, ll b)
    {
        if (!a) return 0;

        int sig = 1;
        if (a < 0) a = -a, sig = -sig;
        if (b < 0) b = -b, sig = -sig;


        ll rst = 0;
        for (; !(b & 1); a >>= 1, b >>= 1);
        if (b == 1) rst = a;
        else for (; b <= a; ++rst)
            a -= b;

        return sig < 0 ? -rst : rst;
    }
public:
    int divide(int dividend, int divisor) {
        ll rst = f(dividend,divisor);
        return rst == int(rst) ? rst : INT_MAX;
    }
};

///暴力
class SolutionV1 {///908 ms 9.81% 5.8M 50.10%
    using ll = long long;
    ll f (ll a, ll b)
    {
        if (!a) return 0;
        if (b == 1) return a;
        if (b == -1) return -a;
        if (b == 2) return a >> 1;
        if (b == -2) return -(a >> 1);

        int sig = 1;
        if (a < 0) a = -a, sig = -sig;
        if (b < 0) b = -b, sig = -sig;

        ll rst = 0;
        for (; b <= a; ++rst)
            a -= b;

        return sig < 0 ? -rst : rst;
    }
public:
    int divide(int dividend, int divisor) {
        ll rst = f(dividend,divisor);
        return rst == int(rst) ? rst : INT_MAX;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pii> xs{{10,3},{-7,3},{-2147483648,-1}, {7,-3},{-1010369383,-2147483648},{11,11},{2147483647,2147483647}};
    for (auto [x,y] : xs)
        print(x,y), print(Solution().divide(x,y)), print("===");
    return 0;
}
#endif
