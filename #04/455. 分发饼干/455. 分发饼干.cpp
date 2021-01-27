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
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

 
示例 1:

输入: g = [1,2,3], s = [1,1]
输出: 1
解释:
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:

输入: g = [1,2], s = [1,2,3]
输出: 2
解释:
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.
 

提示：

1 <= g.length <= 3 * 104
0 <= s.length <= 3 * 104
1 <= g[i], s[j] <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/assign-cookies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

/***************
op[i] 提供类型的第i个字节的比较方式，具体来说有5种取值。
−1：该字节不是排序的关键字。
0：以该字节为基准从小到大排序。
1：以该字节为基准从大到小排序。
2：以该字节为基准从小到大排序，且该字节的最高位是有符号整形的符号位。
3：以该字节为基准从大到小排序，且该字节的最高位是有符号整形的符号位。

例如，对int从小到大排序，则应将{0,0,0,2}传入op。
**************/
#define UC unsigned char
template<typename T>
void Radixsort(T * fst, T * lst, T * buf, int * op)
{
    static int b[0x100];
    int Len = lst - fst, Sz = sizeof(T), at = 0;
    UC * bgn, * end, tmp;
    FOR(i,Sz)
    {
        if (op[i] == -1) continue;
        bgn = (UC*)fst + i;
        end = (UC*)lst + i;

        tmp = ((op[i] & 1) ? 0xff : 0) ^ ((op[i] & 2) ? 0x80 : 0);
        memset(b, 0, sizeof(b));

        for(UC * it = bgn; it != end; it += Sz)
            ++b[tmp ^ *it];

        ffor(j,1,0x100) b[j] += b[j-1];
        for(UC * it = end; it != bgn; buf[--b[tmp ^ *(it -= Sz)]] = *--lst);
        lst = buf + Len;
        swap(fst,buf);
        at^=1;
    }
    if(at)memcpy(buf, fst, Sz * Len);
}



class Solution {///44ms 100.00% 18M 5.02%
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (g.empty() || s.empty()) return 0;
        vector<int> v(max(g.size(), s.size()));
        int op[4] = {0,0,0,2};
        Radixsort(&*begin(g), &*end(g), &*begin(v), op), Radixsort(&*begin(s), &*end(s), &*begin(v), op);
        int rst = 0;
        for (int i = 0, j = 0, n = g.size(), m = s.size(); i < n && j < m; ++j)
            if (g[i] <= s[j]) ++rst, ++i;
        return rst;
    }
};


class SolutionV1 {///88ms 59.17% 17.5M 18.41%
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(begin(g), end(g)), sort(begin(s), end(s));
        int rst = 0;
        for (int i = 0, j = 0, n = g.size(), m = s.size(); i < n && j < m; ++j)
            if (g[i] <= s[j]) ++rst, ++i;
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
