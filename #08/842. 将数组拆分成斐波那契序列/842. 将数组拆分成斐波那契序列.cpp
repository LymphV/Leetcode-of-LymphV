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
给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。

形式上，斐波那契式序列是一个非负整数列表 F，且满足：

0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
F.length >= 3；
对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。

返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。

 

示例 1：

输入："123456579"
输出：[123,456,579]
示例 2：

输入: "11235813"
输出: [1,1,2,3,5,8,13]
示例 3：

输入: "112358130"
输出: []
解释: 这项任务无法完成。
示例 4：

输入："0123"
输出：[]
解释：每个块的数字不能以零开头，因此 "01"，"2"，"3" 不是有效答案。
示例 5：

输入: "1101111"
输出: [110, 1, 111]
解释: 输出 [11,0,11,11] 也同样被接受。
 

提示：

1 <= S.length <= 200
字符串 S 中只含有数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-array-into-fibonacci-sequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 90.56% 6.7M 59.94%
    using sit = string::iterator;
    using vi = vector<int>;
    using ll = long long;
    int toInt (sit l, sit r)
    {
        if (r - l == 0 || r - l != 1 && *l == '0') return -1;
        ll rst = 0;
        for (; l != r; ++l)
        {
            rst = 10 * rst + *l - '0';
            if (INT_MAX < rst) return -1;
        }
        return rst;
    }
    int lenInt (int x)
    {
        if (!x) return 1;
        int rst = 0;
        for (; x; x /= 10, ++rst);
        return rst;
    }
public:
    vector<int> splitIntoFibonacci(string S) {
        auto s = begin(S);
        for (int p = 1, n = S.size(); p * 2 < n; ++p)
        {
            for (int q = 1; p * 2 + q <= n && p + q * 2 <= n; ++q)
            {
                int a = toInt(s, s + p);
                if (a < 0) return {};
                int b = toInt(s + p, s + p + q);
                if (b < 0) break;
                vi rst{a,b};
                ll tot = ll(a) + ll(b);
                if (INT_MAX < tot) break;
                for (int i = p + q, j, c = tot; i < n; i = j, c = tot)
                {
                    j = i + lenInt(c);
                    if (n < j || c != toInt(s + i, s + j)) break;
                    rst.emplace_back(c);
                    if (j == n) return rst;
                    a = b;
                    b = c;
                    tot = ll(a) + ll(b);
                    if (INT_MAX < tot) break;
                }
            }
        }
        return {};
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<string> xs{
        "1011",
        "123456579",
        "11235813",
        "112358130",
        "0123",
        "1101111",
        "214748364721474836422147483641"
    };
    for (auto x : xs)
        print(x), print(Solution().splitIntoFibonacci(x)), print("===");
    return 0;
}
#endif
