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
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:

输入: [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
进阶:

如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///12ms 77.39% 13.3M 15.39%
    using vi = vector<int>;


    int solve (vi & nums, int i, int j, int & maxL, int & maxR, int & tot)
    {
        if (j - i == 1) return maxL = maxR = tot = nums[i];
        if (j - i == 2)
        {
            tot = nums[i] + nums[i + 1];
            return max(maxL = max(nums[i], tot), maxR = max(nums[i + 1], tot));
        }
        int lMaxL, lMaxR, lTot, rMaxL, rMaxR, rTot, m = (i + j) / 2;
        int lRst = solve(nums, i, m, lMaxL, lMaxR, lTot), rRst = solve(nums, m, j, rMaxL, rMaxR, rTot);
        tot = lTot + rTot, maxL = max(lMaxL, lTot + rMaxL), maxR = max(rMaxR, rTot + lMaxR);
        return max({lRst, rRst, lMaxR + rMaxL});
    }
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        int a, b, c;
        return solve(nums, 0, n, a, b, c);
    }
};


class SolutionV6 {///12ms 77.39% 13.3M 28.43%
    using vi = vector<int>;
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        int rst = nums[0];
        ffor(i,1,n)
        {
            if (0 < nums[i - 1]) nums[i] += nums[i - 1];
            rst = max(rst, nums[i]);
        }
        return rst;
    }
};

class SolutionV5 {///12ms 77.39% 13.3M 21.64%
    using vi = vector<int>;
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        ffor(i,1,n) if (nums[i] < nums[i - 1] + nums[i]) nums[i] += nums[i - 1];
        return *max_element(begin(nums), end(nums));
    }
};

class SolutionV4 {///16ms 52.22% 13.1M 47.70%
    using vi = vector<int>;

    int solve (vi & tot, int i, int j, int & minV, int & maxV)
    {
        if (j - i == 2)
        {
            if (tot[i] < tot[i + 1]) minV = tot[i], maxV = tot[i + 1];
            else minV = tot[i + 1], maxV = tot[i];
            return tot[i + 1] - tot[i];
        }
        if (j - i == 1)
        {
            minV = maxV = tot[i];
            return INT_MIN;
        }
        int m = (i + j) / 2;
        int minL, maxL, minR, maxR;
        int rstL = solve(tot,i,m,minL,maxL),  rstR = solve(tot,m,j,minR,maxR);
        minV = min(minL, minR), maxV = max(maxL, maxR);
        return max({rstL, rstR, maxR - minL});
    }
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        partial_sum(begin(nums), end(nums), begin(nums));
        int a, b;
        return max(solve(nums,0,n,a,b), *max_element(begin(nums), end(nums)));
    }
};

class SolutionV3 {///20ms 24.41% 13.3M 15.39%
    using vi = vector<int>;

    int solve (vi & tot, int i, int j, int & minV, int & maxV)
    {
        if (j - i == 2)
        {
            if (tot[i] < tot[i + 1]) minV = tot[i], maxV = tot[i + 1];
            else minV = tot[i + 1], maxV = tot[i];
            return tot[i + 1] - tot[i];
        }
        if (j - i == 1)
        {
            minV = maxV = tot[i];
            return INT_MIN;
        }
        int m = (i + j) / 2;
        int minL, maxL, minR, maxR;
        int rstL = solve(tot,i,m,minL,maxL),  rstR = solve(tot,m,j,minR,maxR);
        minV = min(minL, minR), maxV = max(maxL, maxR);
        return max({rstL, rstR, maxR - minL});
    }
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        vi tot(n + 1, 0);
        ffor(i,1,n+1) tot[i] = tot[i - 1] + nums[i - 1];
        int a, b;
        return solve(tot,0,n+1,a,b);
    }
};

class SolutionV2 {///36ms 6.03% 29.9M 5.14%
    using vi = vector<int>;

    vi solve (vi & tot, int i, int j)
    {
        if (j - i == 2) return {tot[i + 1] - tot[i], min(tot[i], tot[i + 1]), max(tot[i], tot[i + 1])};
        if (j - i == 1) return {INT_MIN, tot[i], tot[i]};///max_sub, min, max
        int m = (i + j) / 2;
        vi && rstL = solve(tot,i,m), && rstR = solve(tot,m,j);
        int minL = rstL[1], maxL = rstL[2], minR = rstR[1], maxR = rstR[2];
        return {max({rstL[0], rstR[0], maxR - minL}), min(minL, minR), max(maxL, maxR)};
    }
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        vi tot(n + 1, 0);
        ffor(i,1,n+1) tot[i] = tot[i - 1] + nums[i - 1];
        return solve(tot,0,n+1)[0];
    }
};

class SolutionV1 {///60ms 5.61% 37M 5.14%
    using vi = vector<int>;

    vi solve (vi & tot, int i, int j)
    {
        if (j - i == 1) return {INT_MIN, tot[i], tot[i]};///max_sub, min, max
        int m = (i + j) / 2;
        vi rstL = solve(tot,i,m), rstR = solve(tot,m,j);
        int minL = rstL[1], maxL = rstL[2], minR = rstR[1], maxR = rstR[2];
        return {max({rstL[0], rstR[0], maxR - minL}), min(minL, minR), max(maxL, maxR)};
    }
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        vi tot(n + 1, 0);
        ffor(i,1,n+1) tot[i] = tot[i - 1] + nums[i - 1];
        print(tot);
        return solve(tot,0,n+1)[0];
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {-2,1,-3,4,-1,2,1,-5,4},
        {-1},
        {}
    };
    for (auto x : xs)
        print(x), print(Solution().maxSubArray(x)), print("===");
    return 0;
}
#endif
