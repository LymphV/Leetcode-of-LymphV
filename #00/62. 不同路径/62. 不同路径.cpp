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
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

 

示例 1：


输入：m = 3, n = 7
输出：28
示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向右 -> 向下
2. 向右 -> 向下 -> 向右
3. 向下 -> 向右 -> 向右
示例 3：

输入：m = 7, n = 3
输出：28
示例 4：

输入：m = 3, n = 3
输出：6
 

提示：

1 <= m, n <= 100
题目数据保证答案小于等于 2 * 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 31.28% 6.1M 74.36%
    using ll = long long;
public:
    int uniquePaths(int m, int n) {
        ll rst = 1;
        for (int i = m + n - 2, j = 1, maxJ = min(m, n) - 1; j <= maxJ; --i, ++j)
            rst = rst * i / j;
        return rst;
    }
};

class SolutionV1 {///4ms 31.28% 6.3M 62.81%
    using ll = long long;
public:
    int uniquePaths(int m, int n) {
        ll rst = 1;
        --m, --n;

        for (int i = m + n, j = 1, maxJ = min(m, n); j <= maxJ; --i, ++j)
            rst = rst * i / j;
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pii> xs{
        {5,5}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().uniquePaths(x,y)), print("===");
    return 0;
}
#endif
