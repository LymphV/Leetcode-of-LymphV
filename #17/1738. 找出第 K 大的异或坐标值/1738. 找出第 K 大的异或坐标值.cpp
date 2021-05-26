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
给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。

 

示例 1：

输入：matrix = [[5,2],[1,6]], k = 1
输出：7
解释：坐标 (0,1) 的值是 5 XOR 2 = 7 ，为最大的值。
示例 2：

输入：matrix = [[5,2],[1,6]], k = 2
输出：5
解释：坐标 (0,0) 的值是 5 = 5 ，为第 2 大的值。
示例 3：

输入：matrix = [[5,2],[1,6]], k = 3
输出：4
解释：坐标 (1,0) 的值是 5 XOR 1 = 4 ，为第 3 大的值。
示例 4：

输入：matrix = [[5,2],[1,6]], k = 4
输出：0
解释：坐标 (1,1) 的值是 5 XOR 2 XOR 1 XOR 6 = 0 ，为第 4 大的值。
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
0 <= matrix[i][j] <= 106
1 <= k <= m * n

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-kth-largest-xor-coordinate-value
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///600ms 44.35% 92.3M 94.56%
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int dp[m][n];
        dp[0][0] = matrix[0][0];
        ffor(i,1,m) dp[i][0] = dp[i - 1][0] ^ matrix[i][0];
        ffor(j,1,n) dp[0][j] = dp[0][j - 1] ^ matrix[0][j];
        ffor(i,1,m) ffor(j,1,n) dp[i][j] = dp[i - 1][j - 1] ^ dp[i][j - 1] ^ dp[i - 1][j] ^ matrix[i][j];
        int * p = dp[0];
        partial_sort(p, p + k, p + m * n, greater<int>());
        return p[k - 1];
    }
};

class SolutionV1 {///440ms 89.96% 92.3M 94.56%
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int dp[m][n];
        dp[0][0] = matrix[0][0];
        ffor(i,1,m) dp[i][0] = dp[i - 1][0] ^ matrix[i][0];
        ffor(j,1,n) dp[0][j] = dp[0][j - 1] ^ matrix[0][j];
        ffor(i,1,m) ffor(j,1,n) dp[i][j] = dp[i - 1][j - 1] ^ dp[i][j - 1] ^ dp[i - 1][j] ^ matrix[i][j];
        int * p = dp[0];
        sort(p, p + m * n);
        return p[m * n - k];
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
