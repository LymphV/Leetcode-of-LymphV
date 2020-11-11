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
给定一个整数数组 nums，返回区间和在 [lower, upper] 之间的个数，包含 lower 和 upper。
区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。

说明:
最直观的算法复杂度是 O(n2) ，请在此基础上优化你的算法。

示例:

输入: nums = [-2,5,-1], lower = -2, upper = 2,
输出: 3
解释: 3个区间分别是: [0,0], [2,2], [0,2]，它们表示的和分别为: -2, -1, 2。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-of-range-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///归并排序
class Solution {///116ms 11.26% 35.1M 5.03%
    using ll = long long;
    int lower, upper;
    int solve (vector<ll> & ns, int l, int r)
    {
        if (l + 1 == r) return 0;
        int m = (l + r) / 2, rst = 0;
        rst += solve(ns, l, m);
        rst += solve(ns, m, r);

        int i = l;
        ffor(k,m,r)
        {
            while (i < m && upper < ns[k] - ns[i]) ++i;
            int j = i;
            while (j < m && lower <= ns[k] - ns[j]) ++j;
            rst += j - i;
        }

        auto start = begin(ns);
        vector<ll> a(start + l, start + m), b(start + m, start + r);
        merge(begin(a), end(a), begin(b), end(b), start + l);
        return rst;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        this->lower = lower, this->upper = upper;
        vector<ll> ns{0};
        for(int & x : nums) ns.emplace_back(x);
        partial_sum(begin(ns), end(ns), begin(ns));
        return solve(ns, 0, n + 1);
    }
};

///n^2
class SolutionV1 {///TLE
    using ll = long long;
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<ll> ns(begin(nums), end(nums));
        partial_sum(begin(ns), end(ns), begin(ns));
        vector<vector<ll>> tot(n + 1, vector<ll>(n + 1, 0));
        ffor(j,1,n+1) tot[0][j] = ns[j - 1];
        ffor(i,1,n)ffor(j,i+1,n+1) tot[i][j] = tot[0][j] - tot[0][i];
        int rst = 0;
        FOR(i,n)ffor(j,i+1,n+1) if (lower <= tot[i][j] && tot[i][j] <= upper) ++rst;
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,pii>> xs{
        {{-2,5,-1},{-2,2}}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().countRangeSum(x,y.first,y.second)), print("===");
    return 0;
}
#endif
