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
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：

输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶
示例 2：

输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/climbing-stairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class SolutionV2 ///0ms 100.00% 6M 58.06%
{
public:
    int climbStairs (int n)
    {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        int a = 1, b = 2;
        for (int i = 3; i <= n; ++i)
        {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};

class SolutionV1 {///0ms 100.00% 6.2M 41.54%
    using ll = long long;
    int com (int n, int m)
    {
        ll rst = 1;
        m = min(m, n - m);
        for (int i = n, j = 1; j <= m; ++j, --i)
            rst = rst * i / j;
        return rst;
    }

public:
    int climbStairs(int n) {
        int rst = 0;
        for (int i = 0; i * 2 <= n; ++i)
            rst += com(n - i, i);
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<int> xs{2,3, 44};
    for (auto x : xs)
        print(x), print(Solution().climbStairs(x)), print("===");
    return 0;
}
#endif
