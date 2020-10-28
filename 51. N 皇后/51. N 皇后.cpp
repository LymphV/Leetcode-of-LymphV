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

给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

示例：

输入：4
输出：[
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。
 

提示：

皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 99.09% 7.9M 42.33%
    using vi = vector<int>;
    using vs = vector<string>;
    vector<vs> rst;
    vs now;
    vi board, col, add, sub;
    int n;

    string decode (int j)
    {
        string rst(n, '.');
        rst[j] = 'Q';
        return rst;
    }

    void f(int i = 0)
    {
        if (i == n)
        {
            rst.emplace_back(now);
            return;
        }
        FOR(j, n)
        {
            if (col[j] || add[i + j] || sub [n + i - j]) continue;
            col[j] = add[i + j] = sub[n + i - j] = 1;
            now.emplace_back(decode(j));
            f(i + 1);
            col[j] = add[i + j] = sub[n + i - j] = 0;
            now.pop_back();
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        now = {}, board = vi(n,-1), col = vi(n,0), add = vi(2 * n,0), sub = vi(2 * n,0);
        rst = {};
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
        print(x), print(Solution().solveNQueens(x)), print("===");
    return 0;
}
#endif
