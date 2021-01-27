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
给定一个已排序的正整数数组 nums，和一个正整数 n 。从 [1, n] 区间内选取任意个数字补充到 nums 中，使得 [1, n] 区间内的任何数字都可以用 nums 中某几个数字的和来表示。请输出满足上述要求的最少需要补充的数字个数。

示例 1:

输入: nums = [1,3], n = 6
输出: 1
解释:
根据 nums 里现有的组合 [1], [3], [1,3]，可以得出 1, 3, 4。
现在如果我们将 2 添加到 nums 中， 组合变为: [1], [2], [3], [1,3], [2,3], [1,2,3]。
其和可以表示数字 1, 2, 3, 4, 5, 6，能够覆盖 [1, 6] 区间里所有的数。
所以我们最少需要添加一个数字。
示例 2:

输入: nums = [1,5,10], n = 20
输出: 2
解释: 我们需要添加 [2, 4]。
示例 3:

输入: nums = [1,2,2], n = 5
输出: 0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/patching-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///16ms 43.78% 11.4M 64.64%
    using vi = vector<int>;
    using ll = long long;
public:
    int minPatches(vector<int>& nums, int n) {
        int rst = 0;
        ll cover = 0;

        for (int x : nums)
        {
            while (cover < n && cover + 1 < x)
                ++rst, cover += cover + 1;
            if (n <= cover) break;
            cover += x;
        }
        while (cover < n)
            ++rst, cover += cover + 1;

        return rst;
    }
};


class SolutionV1 {///0.0
    using vi = vector<int>;

public:
    int minPatches(vector<int>& nums, int n) {
        set<int> s {0};
        vi v(n + 1, 0);
        for (int x : nums) for (int y : set<int>(s)) if (1 <= x + y && x + y <= n && !v[x + y])
        {
            v[x + y] = 1;
            s.insert(x + y);
        }
        else if (n < x + y) break;
        int rst = 0;
        ffor(i,1,n+1) if (!v[i])
        {
            ++rst;
            for (int y : set<int>(s)) if (1 <= i + y && i + y <= n && !v[i + y])
            {
                v[i + y] = 1;
                s.insert(i + y);
            }
            else if (n < i + y) break;
            if (s.size() == n + 1) return rst;
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{1,3},6},
        {{1,5,10},20},
        {{1,2,2},5},
        {{},1}
    };
    for (auto &[x,y] : xs)
        print(x,y), print(Solution().minPatches(x,y)), print("===");
    return 0;
}
#endif
