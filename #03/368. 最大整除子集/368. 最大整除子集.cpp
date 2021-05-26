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
给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，子集中每一元素对 (answer[i], answer[j]) 都应当满足：
answer[i] % answer[j] == 0 ，或
answer[j] % answer[i] == 0
如果存在多个有效解子集，返回其中任何一个均可。

 

示例 1：

输入：nums = [1,2,3]
输出：[1,2]
解释：[1,3] 也会被视为正确答案。
示例 2：

输入：nums = [1,2,4,8]
输出：[1,2,4,8]
 

提示：

1 <= nums.length <= 1000
1 <= nums[i] <= 2 * 109
nums 中的所有整数 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-divisible-subset
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///48ms 71.97% 8.5M 67.01%
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));
        int dp[n], last[n];
        MS(dp,0), MS(last,-1);
        ffor(i,1,n) FOR(j,i) if (nums[i] % nums[j] == 0 && dp[i] <= dp[j])
            last[i] = j, dp[i] = dp[j] + 1;
        int maxE = max_element(dp, dp + n) - dp;
        vector<int> rst(dp[maxE] + 1);
        for (int i = dp[maxE], j = maxE; ~i; --i, j = last[j])
            rst[i] = nums[j];
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,2,4,8}
    };
    for (auto &x : xs)
        print(x), print(Solution().largestDivisibleSubset(x)), print("===");
    return 0;
}
#endif
