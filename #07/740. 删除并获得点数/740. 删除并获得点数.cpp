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
给你一个整数数组 nums ，你可以对它进行一些操作。

每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除每个等于 nums[i] - 1 或 nums[i] + 1 的元素。

开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。

 

示例 1：

输入：nums = [3,4,2]
输出：6
解释：
删除 4 获得 4 个点数，因此 3 也被删除。
之后，删除 2 获得 2 个点数。总共获得 6 个点数。
示例 2：

输入：nums = [2,2,3,3,3,4]
输出：9
解释：
删除 3 获得 3 个点数，接着要删除两个 2 和 4 。
之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
总共获得 9 个点数。
 

提示：

1 <= nums.length <= 2 * 104
1 <= nums[i] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/delete-and-earn
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///12ms 27.37% 8.9M 78.25%
    using vi = vector<int>;
public:
    int deleteAndEarn(vector<int>& nums) {
        sort(rbegin(nums), rend(nums));
        int m = nums.size();
        vi vs{nums[0]};
        ffor(i,1,m) if (nums[i] != nums[i - 1])
            vs.emplace_back(nums[i]);

        int n = vs.size();
        int cnt[n];
        cnt[0] = 1;
        for(int i = 1, j = 0; i < m; ++i)
            if (nums[i] != nums[i - 1]) cnt[++j] = 1;
            else ++cnt[j];



        if (n == 1) return nums[0] * cnt[0];

        int a = vs[0] * cnt[0];
        int b = max(a, vs[1] + 1 < vs[0] ? a + vs[1] * cnt[1] : vs[1] * cnt[1]);

        ffor(i,2,n)
        {
            int c = max(b, (vs[i] + 1 < vs[i - 1] ? b : a) + vs[i] * cnt[i]);
            a = b;
            b = c;
        }

        print(vs);
        print(vi(cnt,cnt+n));
        return b;
    }
};

class SolutionV2 {///8ms 60.06% 8.8M 87.28%
    using vi = vector<int>;
public:
    int deleteAndEarn(vector<int>& nums) {
        sort(rbegin(nums), rend(nums));
        int m = nums.size();
        vi vs{nums[0]};
        ffor(i,1,m) if (nums[i] != nums[i - 1])
            vs.emplace_back(nums[i]);

        int n = vs.size();
        int dp[n], cnt[n], rst[n];
        cnt[0] = 1;
        for(int i = 1, j = 0; i < m; ++i)
            if (nums[i] != nums[i - 1]) cnt[++j] = 1;
            else ++cnt[j];



        if (n == 1) return nums[0] * cnt[0];

        rst[0] = dp[0] = vs[0] * cnt[0];
        dp[1] = vs[1] + 1 < vs[0] ? dp[0] + vs[1] * cnt[1] : vs[1] * cnt[1];
        rst[1] = max(rst[0], dp[1]);

        ffor(i,2,n)
        {
            dp[i] = (vs[i] + 1 < vs[i - 1] ? rst[i - 1] : rst[i - 2]) + vs[i] * cnt[i];
            rst[i] = max(rst[i - 1], dp[i]);
        }

        print(vs);
        print(vi(cnt,cnt+n));
        print(vi(rst,rst+n));
        print (vi(dp,dp+n));
        return rst[n - 1];
    }
};

class SolutionV1 {///12ms 27.37% 9.5M 41.72%
public:
    int deleteAndEarn(vector<int>& nums) {
        map<int,int> mp;
        for (int x : nums) ++mp[x];
        int n = mp.size();
        if (n == 1) return nums[0] * mp[nums[0]];
        int dp[n], vs[n], cnt[n], rst[n];
        int i = n - 1;
        for (auto [k, v] : mp)
        {
            vs[i] = k, cnt[i] = v;
            --i;
        }

        rst[0] = dp[0] = vs[0] * cnt[0];
        dp[1] = vs[1] + 1 < vs[0] ? dp[0] + vs[1] * cnt[1] : vs[1] * cnt[1];
        rst[1] = max(rst[0], dp[1]);

        ffor(i,2,n)
        {
            dp[i] = (vs[i] + 1 < vs[i - 1] ? rst[i - 1] : rst[i - 2]) + vs[i] * cnt[i];
            rst[i] = max(rst[i - 1], dp[i]);
        }

        print(vi(rst,rst+n));
        print(mp);
        print (vi(dp,dp+n));
        return rst[n - 1];
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {3,1},
        {1,1,1,2,4,5,5,5,6},
        {8,10,4,9,1,3,5,9,4,10},
        {2,2,3,3,3,4}
    };
    for (auto & x : xs)
        print(x), print(Solution().deleteAndEarn(x)), print("===");
    return 0;
}
#endif
