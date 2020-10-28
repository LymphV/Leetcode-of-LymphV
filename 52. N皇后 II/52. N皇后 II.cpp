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
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:

输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
 

提示：

皇后，是国际象棋中的棋子，意味着国王的妻子。皇后只做一件事，那就是“吃子”。当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。当然，她横、竖、斜都可走一或 N-1 步，可进可退。（引用自 百度百科 - 皇后 ）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///0ms 100.00% 6.1M 49.2%
    using vi = vector<int>;
    int rst;
    vi col, add, sub;
    int n;

    void f(int i = 0)
    {
        if (i == n)
        {
            ++rst;
            return;
        }
        FOR(j, n)
        {
            if (col[j] || add[i + j] || sub [n + i - j]) continue;
            col[j] = add[i + j] = sub[n + i - j] = 1;
            f(i + 1);
            col[j] = add[i + j] = sub[n + i - j] = 0;
        }
    }
public:
    int totalNQueens(int n) {
        col = vi(n,0), add = vi(2 * n,0), sub = vi(2 * n,0);
        rst = 0;
        this->n = n;

        f();
        return rst;
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<int> xs{1, 2, 3, 4};
    for (auto x : xs)
        print(x), print(Solution().totalNQueens(x)), print("===");
    return 0;
}
#endif
