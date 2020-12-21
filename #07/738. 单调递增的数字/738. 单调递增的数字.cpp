#if defined(LocalLymphV)
#include "../../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增。

（当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。）

示例 1:

输入: N = 10
输出: 9
示例 2:

输入: N = 1234
输出: 1234
示例 3:

输入: N = 332
输出: 299
说明: N 是在 [0, 10^9] 范围内的一个整数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/monotone-increasing-digits
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 6.4M 10.81%
    using vi = vector<int>;
    using vrit = vi::reverse_iterator;

    bool solve (vrit left, vrit right, vi & rst)
    {
        if (left == right) return 1;
        if (!rst.empty() && *left < rst.back()) return 0;

        int i = *left;
        if (rst.empty() || rst.back() <= i)
        {
            rst.emplace_back(i);
            if (solve(left + 1, right, rst)) return 1;
            rst.pop_back();
        }

        --i;
        if (rst.empty() || rst.back() <= i)
        {
            rst.emplace_back(i);
            for (++left; left != right; ++left) rst.emplace_back(9);
            return 1;
        }
        return 0;
    }

public:
    int monotoneIncreasingDigits(int N) {
        if (N < 10) return N;
        string s = to_string(N);
        vi a, b;
        for (; N; N /= 10) a.emplace_back(N % 10);
        solve(rbegin(a), rend(a), b);
        int rst = 0;
        for (int x : b) rst = rst * 10 + x;
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<int> xs{
        10,
        1234,
        332
    };
    for (auto x : xs)
        print(x), print(Solution().monotoneIncreasingDigits(x)), print("===");
    return 0;
}
#endif
