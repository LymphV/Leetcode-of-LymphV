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
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，能够偷窃到的最高金额。

 

示例 1：

输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
示例 2：

输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 3：

输入：nums = [0]
输出：0
 

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 7.6M 76.62%
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        int a, b, c;
        a = 0, b = nums[0];
        ffor(i,2,n)
        {
            c = max(nums[i - 1] + a, b);
            a = b;
            b = c;
        }
        int rst = b;
        a = 0, b = nums[1];
        ffor(i,2,n)
        {
            c = max(nums[i] + a, b);
            a = b;
            b = c;
        }
        return max(rst, b);
    }
};

class SolutionV2 {///0ms 100.00% 7.6M 63.63%
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        int dp[n];
        dp[0] = 0, dp[1] = nums[0];
        ffor(i,2,n) dp[i] = max(nums[i - 1] + dp[i - 2], dp[i - 1]);
        int rst = dp[n - 1];
        dp[0] = 0, dp[1] = nums[1];
        ffor(i,2,n) dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
        return max(rst, dp[n - 1]);
    }
};

class SolutionV1 {///0ms 100.00% 8.4M 5.01%
    using vi = vector<int>;
    using vvi = vector<vi>;
    vvi dp;
    int solve (int i, int j, vi & nums)
    {
        if (j < i) return 0;
        if (i == j) return nums[i];
        if (0 <= dp[i][j]) return dp[i][j];
        return dp[i][j] = max(nums[i] + solve(i + 2, j, nums), solve(i + 1, j, nums));
    }
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        dp = vvi(n, vi(n, -1));
        return max(nums[0] + solve(2,n-2,nums), solve(1,n-1,nums));
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{{0,0}};
    for (auto &x : xs)
        print(x), print(Solution().rob(x)), print("===");
    return 0;
}
#endif
