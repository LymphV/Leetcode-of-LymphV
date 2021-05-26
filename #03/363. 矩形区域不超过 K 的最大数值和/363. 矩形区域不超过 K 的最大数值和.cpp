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
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。

 

示例 1：


输入：matrix = [[1,0,1],[0,-2,3]], k = 2
输出：2
解释：蓝色边框圈出来的矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。
示例 2：

输入：matrix = [[2,2,-1]], k = 3
输出：3
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-100 <= matrix[i][j] <= 100
-105 <= k <= 105
 

进阶：如果行数远大于列数，该如何设计解决方案？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///466ms 49.91% 8M 98.30%
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int rst = -101 * m * n;
        int tot[m + 1][n + 1];
        FOR(i,m+1) tot[i][0] = 0;
        FOR(j,n+1) tot[0][j] = 0;
        ffor(i,1,m+1)ffor(j,1,n+1)
            tot[i][j] = tot[i][j - 1] + tot[i - 1][j] - tot[i - 1][j - 1] + matrix[i - 1][j - 1];
        FOR(il,m)ffor(ir,il+1,m+1)FOR(jl,n)ffor(jr,jl+1,n+1)
        {
            int t = tot[ir][jr] + tot[il][jl] - tot[il][jr] - tot[ir][jl];
            if (t <= k && rst < t) rst = t;
        }
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
