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
给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。

你需要返回给定数组中的重要翻转对的数量。

示例 1:

输入: [1,3,2,3,1]
输出: 2
示例 2:

输入: [2,4,3,5,1]
输出: 3
注意:

给定数组的长度不会超过50000。
输入数组中的所有数字都在32位整数的表示范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///980ms 10.47% 146.5M 8.05%
    using ll = long long;


    int solve (vector<int> & ns, int l, int r)
    {
        if (r - l <= 1) return 0;
        int m = (l + r) / 2, rst = 0;
        rst += solve(ns, l, m);
        rst += solve(ns, m, r);


        for (int i = l, j = m; j < r; ++j)
        {
            ll v = ll(ns[j]) * 2;
            if (INT_MAX < v) break;
            if (INT_MIN <= v) for (int vv = v; i < m && ns[i] <= vv; ++i);
            rst += m - i;
        }

        auto start = begin(ns);

        vector<int> a(start + l, start + m), b(start + m, start + r);
        merge(begin(a), end(a), begin(b), end(b), start + l);
        return rst;
    }
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;

        return solve(nums, 0, n);
    }
};


class SolutionV3 {///1004ms 9.80% 174.5M 5.03%
    using ll = long long;


    int solve (vector<ll> & ns, int l, int r)
    {
        if (r - l <= 1) return 0;
        int m = (l + r) / 2, rst = 0;
        rst += solve(ns, l, m);
        rst += solve(ns, m, r);


        for (int i = l, j = m; j < r; ++j)
        {
            for (ll v = ns[j] * 2; i < m && ns[i] <= v; ++i);
            rst += m - i;
        }

        auto start = begin(ns);

        vector<ll> a(start + l, start + m), b(start + m, start + r);
        merge(begin(a), end(a), begin(b), end(b), start + l);
        return rst;
    }

public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;

        vector<ll> ns{begin(nums), end(nums)};

        return solve(ns, 0, n);
    }
};


class SolutionV2 {///
    using ll = long long;


    int solve (vector<ll> & ns, int l, int r)
    {
        if (r - l <= 1) return 0;
        int m = (l + r) / 2, rst = 0;
        rst += solve(ns, l, m);
        rst += solve(ns, m, r);

        auto start = begin(ns);
        ffor(i,m,r) rst += (start + m) - upper_bound(start + l, start + m, ns[i] * 2);

        vector<ll> a(start + l, start + m), b(start + m, start + r);
        merge(begin(a), end(a), begin(b), end(b), start + l);
        return rst;
    }

public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;

        vector<ll> ns{begin(nums), end(nums)};

        return solve(ns, 0, n);
    }
};

class SolutionV1 {///TLE
    using ll = long long;
public:
    int reversePairs(vector<int>& nums) {
        int rst = 0, n = nums.size();
        if (n < 2) return 0;
        map<ll,int,greater<ll>> cnt;
        for (auto i = rbegin(nums); i != rend(nums); ++i)
        {
            cnt[*i];
            auto j = cnt.find(*i);
            for (++j; j != end(cnt); ++j) rst += j->second;
            ++cnt[ll(*i) * 2];
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,3,2,3,1},
        {2,4,3,5,1},
        {}
    };
    for (auto x : xs)
        print(x), print(Solution().reversePairs(x)), print("===");
    return 0;
}
#endif
