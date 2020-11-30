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
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///贪心
class Solution {///28ms 26.21% 15.6M 5.62%
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        if (n - 1 <= nums[0]) return 1;
        int rst = 0;
        for (int i = 0, j = 1; i < n - 1; ++rst)
        {
            int next = i;
            for (; j < n && j <= i + nums[i]; ++j)
                if (n - 1 <= j + nums[j]) return rst + 2;
                else if (next + nums[next] <= j + nums[j])
                     next = j;
            i = next;
        }
        return rst;
    }
};



///贪心
class Solution {///28ms 26.21% 15.6M 5.17%
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        int rst = 0;
        for (int i = 0; i < n - 1; ++rst)
        {
            if (n - 1 <= i + nums[i])
            {
                i = n - 1;
                continue;
            }
            int next = i + 1;
            for (int j = i + 2; j < n && j <= i + nums[i]; ++j)
                if (next + nums[next] < j + nums[j])
                     next = j;
            i = next;
        }
        return rst;
    }
};


class SolutionV1 {///TLE
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        if (n - 1 <= nums[0]) return 1;
        vector<int> dp(n, 0);
        for (int i = n - 2; ~i; --i)
        {
            if (n - 1 <= i + nums[i])
            {
                dp[i] = 1;
                continue;
            }
            dp[i] = dp[i + 1];
            for (int j = i + 2; j < n && j <= i + nums[i]; ++j)
                dp[i] = min(dp[i], dp[j]);
            ++dp[i];
        }
        return dp[0];
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
