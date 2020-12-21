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
给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。

求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。

说明: 请尽可能地优化你算法的时间和空间复杂度。

示例 1:

输入:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
输出:
[9, 8, 6, 5, 3]
示例 2:

输入:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
输出:
[6, 7, 6, 0, 4]
示例 3:

输入:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
输出:
[9, 8, 9]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/create-maximum-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution///164ms 69.71% 23.6M 70.66%
{
    using vi = vector<int>;
    using vit = vi::iterator;

    vi maxNumber(vi & ns, int k)///单调栈
    {
        if (!k) return {};
        vi rst;
        vit l = begin(ns), r = end(ns);
        for(; l < r; ++l)
        {
            while (!rst.empty() && rst.back() < *l && k < r - l)
                rst.pop_back(), ++k;
            if (r - l == k) break;

            if (k) rst.emplace_back(*l), --k;
        }
        rst.insert(end(rst), l, r);
        return rst;
    }

    bool cmp (vit l1, vit r1, vit l2, vit r2)
    {
        for (; l1 != r1 && l2 != r2 && *l1 == *l2; ++l1, ++l2);
        if (l1 == r1) return 1;
        if (l2 == r2) return 0;
        return *l1 < *l2;
    }

    vi merge (vi & a, vi & b)
    {
        vi rst;
        for (vit l1 = begin(a), r1 = end(a), l2 = begin(b), r2 = end(b); l1 < r1 || l2 < r2; )
        {
            if (cmp(l1,r1,l2,r2))
            {
                rst.emplace_back(*l2);
                ++l2;
            }
            else
            {
                rst.emplace_back(*l1);
                ++l1;
            }
        }
        return rst;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vi rst;
        for (int i = 0, j = k, m = nums1.size(), n = nums2.size(); i <= k; ++i, --j)
        {
            if (m < i || n < j) continue;
            vi a = maxNumber(nums1, i), b = maxNumber(nums2, j);
            rst = max(rst, merge(a,b));
        }
        return rst;
    }
};



class SolutionV3///152ms 73.48% 23.8M 70.48%
{
    using vi = vector<int>;
    using vit = vi::iterator;

    vi maxNumber(vi & ns, int k)
    {
        if (!k) return {};
        vi rst;
        vit l = begin(ns), r = end(ns);
        for(; l < r; ++l)
        {
            while (!rst.empty() && rst.back() < *l && k < r - l)
                rst.pop_back(), ++k;
            if (r - l == k) break;

            if (k) rst.emplace_back(*l), --k;
        }
        rst.insert(end(rst), l, r);
        return rst;
    }

    bool cmp (vit l1, vit r1, vit l2, vit r2)
    {
        for (; l1 != r1 && l2 != r2 && *l1 == *l2; ++l1, ++l2);
        if (l1 == r1) return 1;
        if (l2 == r2) return 0;
        return *l1 < *l2;
    }

    vi merge (vi & a, vi & b)
    {
        vi rst;
        for (vit l1 = begin(a), r1 = end(a), l2 = begin(b), r2 = end(b); l1 < r1 || l2 < r2; )
        {
            if (cmp(l1,r1,l2,r2))
            {
                rst.emplace_back(*l2);
                ++l2;
            }
            else
            {
                rst.emplace_back(*l1);
                ++l1;
            }
        }
        return rst;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vi> rst;
        for (int i = 0, j = k, m = nums1.size(), n = nums2.size(); i <= k; ++i, --j)
        {
            if (m < i || n < j) continue;
            vi a = maxNumber(nums1, i), b = maxNumber(nums2, j);
            print (a,b);
            rst.emplace_back(merge(a,b));
        }
        return *max_element(begin(rst), end(rst));
    }
};


class SolutionV2///WA
{
    using vi = vector<int>;
    using vit = vi::iterator;

    vi maxNumber(vi & ns, int k)
    {
        if (!k) return {};
        vi rst;
        vit l = begin(ns), r = end(ns);
        for(; l < r; ++l)
        {
            while (!rst.empty() && rst.back() < *l && k < r - l)
                rst.pop_back(), ++k;
            if (r - l == k) break;

            if (k) rst.emplace_back(*l), --k;
        }
        rst.insert(end(rst), l, r);
        return rst;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vi> rst;
        for (int i = 0, j = k, m = nums1.size(), n = nums2.size(); i <= k; ++i, --j)
        {
            if (m < i || n < j) continue;
            vi a = maxNumber(nums1, i), b = maxNumber(nums2, j), c(k);
            merge(begin(a), end(a), begin(b), end(b), begin(c), greater<int>());
            rst.emplace_back(c);
        }
        return *max_element(begin(rst), end(rst));
    }
};

class SolutionV1///WA
{
    using vi = vector<int>;
    using vit = vi::iterator;
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vi rst;
        for (vit l1 = begin(nums1), r1 = end(nums1), l2 = begin(nums2), r2 = end(nums2); k; --k)
        {
            vit m1 = k - 1 <= r2 - l2 ? r1 : r1 - (k - 1 - (r2 - l2));
            vit m2 = k - 1 <= r1 - l1 ? r2 : r2 - (k - 1 - (r1 - l1));
            vit a = max_element(l1, m1), b = max_element(l2, m2);
            if (l1 == m1)
            {
                rst.emplace_back(*b);
                l2 = b + 1;
            }
            else if (l2 == m2)
            {
                rst.emplace_back(*a);
                l1 = a + 1;
            }
            else if (*a < *b)
            {
                rst.emplace_back(*b);
                l2 = b + 1;
            }
            else
            {
                rst.emplace_back(*a);
                l1 = a + 1;
            }
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<pair<vi,vi>,int>> xs{
        {{{3,4,6,5},{9,1,2,5,8,3}},5},
        {{{2,5,6,4,4,0},{7,3,8,0,6,5,7,6,2}},15},
        {{{6,7},{6,0,4}},5},
        {{{3,9},{8,9}},3}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().maxNumber(x.first,x.second,y)), print("===");
    return 0;
}
#endif
