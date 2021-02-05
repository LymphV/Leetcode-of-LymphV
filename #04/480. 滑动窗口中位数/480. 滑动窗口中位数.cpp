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
中位数是有序序列最中间的那个数。如果序列的长度是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

例如：

[2,3,4]，中位数是 3
[2,3]，中位数是 (2 + 3) / 2 = 2.5
给你一个数组 nums，有一个长度为 k 的窗口从最左端滑动到最右端。窗口中有 k 个数，每次窗口向右移动 1 位。你的任务是找出每次窗口移动后得到的新窗口中元素的中位数，并输出由它们组成的数组。

 

示例：

给出 nums = [1,3,-1,-3,5,3,6,7]，以及 k = 3。

窗口位置                      中位数
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7      -1
 1  3 [-1  -3  5] 3  6  7      -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
 因此，返回该滑动窗口的中位数数组 [1,-1,-1,3,5,6]。

 

提示：

你可以假设 k 始终有效，即：k 始终小于输入的非空数组的元素个数。
与真实值误差在 10 ^ -5 以内的答案将被视作正确答案。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sliding-window-median
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

void f (const multiset<int> & ms)
{
    cout << ms.size();
    cout << "{";
    for (int x : ms) cout << x << ", ";
    cout << "}" << endl;
}


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///52ms 91.53% 17.5M 19.15%
    using vd = vector<double>;
    using vi = vector<int>;
    using ll = long long;
    double mid (multiset<int> & left, multiset<int> & right, int k)
    {
        return k & 1 ? *rbegin(left) : (ll(*rbegin(left)) + ll(*begin(right))) / 2.;
    }

    void add (multiset<int> & left, multiset<int> & right, int x)
    {
        if (x < *rbegin(left))
        {
            auto it = end(left);
            --it;
            right.insert(*it);
            left.erase(it);
            left.insert(x);
        }
        else right.insert(x);
    }

    void rmv (multiset<int> & left, multiset<int> & right, int x)
    {
        if (x <= *rbegin(left))
        {
            auto it = begin(right);
            left.erase(left.find(x));
            left.insert(*it);
            right.erase(it);
        }
        else right.erase(right.find(x));
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int m = (k + 1) / 2;

        multiset<int> left{begin(nums), begin(nums) + m}, right;
        ffor(i,m,k) add(left,right,nums[i]);
        vd rst{mid(left,right,k)};
        for (int i = 0, j = k, n = nums.size(); j < n; ++i, ++j)
        {
            add(left,right,nums[j]);
            rmv(left,right,nums[i]);
            rst.emplace_back(mid(left,right,k));
        }
        return rst;
    }
};

class SolutionV2 {///460ms 6.26% 15.5M 51.34%
    using vd = vector<double>;
    using vi = vector<int>;
    double mid (map<int,int> & mp, int k)
    {
        auto it = begin(mp);
        int m = (k - 1) / 2, i = 0;
        for (; i + it->second <= m; ++it) i += it->second;
        if (k & 1) return it->first;
        if (m + 1 < i + it->second) return it->first;
        double rst = it->first;;
        return (rst + (++it)->first) / 2.;
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        map<int,int> mp;
        FOR(i,k) ++mp[nums[i]];
        vd rst{mid(mp,k)};
        if (!--mp[nums[0]]) mp.erase(nums[0]);
        for (int i = 1, j = k, n = nums.size(); j < n; ++i, ++j)
        {
            ++mp[nums[j]];
            rst.emplace_back(mid(mp,k));
            if (!--mp[nums[i]]) mp.erase(nums[i]);
        }
        return rst;
    }
};

class SolutionV1 {///292ms 16.21% 15.5M 51.34%
    using vd = vector<double>;
    using vi = vector<int>;
    double mid (multiset<int> & ms, int k)
    {
        auto it = begin(ms);
        int m = (k - 1) / 2;
        FOR(i,m) ++it;
        if (k & 1) return *it;
        double rst = *it;
        return (rst + *(++it)) / 2.;
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> ms{begin(nums), begin(nums) + k};
        vd rst{mid(ms,k)};
        ms.erase(ms.find(nums[0]));
        for (int i = 1, j = k, n = nums.size(); j < n; ++i, ++j)
        {
            ms.insert(nums[j]);
            rst.emplace_back(mid(ms,k));
            ms.erase(ms.find(nums[i]));
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{5,5,8,1,4,7,1,3,8,4}, 8},
        {{1,3,-1,-3,5,3,6,7},3},
        {{2147483647,2147483647},2}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().medianSlidingWindow(x, y)), print("===");
    return 0;
}
#endif
