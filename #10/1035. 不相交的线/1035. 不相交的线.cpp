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
在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。

现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足满足：

 nums1[i] == nums2[j]
且绘制的直线不与任何其他连线（非水平线）相交。
请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

以这种方法绘制线条，并返回可以绘制的最大连线数。

 

示例 1：


输入：nums1 = [1,4,2], nums2 = [1,2,4]
输出：2
解释：可以画出两条不交叉的线，如上图所示。
但无法画出第三条不相交的直线，因为从 nums1[1]=4 到 nums2[2]=4 的直线将与从 nums1[2]=2 到 nums2[1]=2 的直线相交。
示例 2：

输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
输出：3
示例 3：

输入：nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
输出：2
 

提示：

1 <= nums1.length <= 500
1 <= nums2.length <= 500
1 <= nums1[i], nums2[i] <= 2000
 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/uncrossed-lines
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///12ms 92.18% 9.5M 96.09%
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int dp[m][n];
        dp[0][0] = nums1[0] == nums2[0];
        ffor(i,1,m) dp[i][0] = nums1[i] == nums2[0] ? 1 : dp[i - 1][0];
        ffor(j,1,n)dp[0][j] = nums1[0] == nums2[j] ? 1 : dp[0][j - 1];
        ffor(i,1,m)ffor(j,1,n)
            dp[i][j] = nums1[i] == nums2[j] ? dp[i - 1][j - 1] + 1 :
                max(dp[i - 1][j], dp[i][j - 1]);
        return dp[m - 1][n - 1];
    }
};


class SolutionV1 {///24ms 29.00% 9.5M 94.83%
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int dp[m][n];
        dp[0][0] = nums1[0] == nums2[0];
        ffor(i,1,m) dp[i][0] = nums1[i] == nums2[0] ? 1 : dp[i - 1][0];
        ffor(j,1,n)dp[0][j] = nums1[0] == nums2[j] ? 1 : dp[0][j - 1];
        ffor(i,1,m)ffor(j,1,n)
            dp[i][j] = nums1[i] == nums2[j] ? dp[i - 1][j - 1] + 1 :
                max({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        return dp[m - 1][n - 1];
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,vi>> xs{

        {{1,4,2},{1,2,4}}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().maxUncrossedLines(x, y)), print("===");
    return 0;
}
#endif
