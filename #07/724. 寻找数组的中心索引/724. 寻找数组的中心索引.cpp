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
给定一个整数类型的数组 nums，请编写一个能够返回数组 “中心索引” 的方法。

我们是这样定义数组 中心索引 的：数组中心索引的左侧所有元素相加的和等于右侧所有元素相加的和。

如果数组不存在中心索引，那么我们应该返回 -1。如果数组有多个中心索引，那么我们应该返回最靠近左边的那一个。

 

示例 1：

输入：
nums = [1, 7, 3, 6, 5, 6]
输出：3
解释：
索引 3 (nums[3] = 6) 的左侧数之和 (1 + 7 + 3 = 11)，与右侧数之和 (5 + 6 = 11) 相等。
同时, 3 也是第一个符合要求的中心索引。
示例 2：

输入：
nums = [1, 2, 3]
输出：-1
解释：
数组中不存在满足此条件的中心索引。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-pivot-index
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///32ms 88.56% 30.2M 91.19%
    using vi = vector<int>;
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        if (!n) return -1;
        int tot = accumulate(begin(nums), end(nums), 0), now = 0;
        FOR(i,n)
        {
            if (now * 2 + nums[i] == tot) return i;
            now += nums[i];
        }
        return -1;
    }
};


class SolutionV1 {///32ms 88.56% 30.7M 45.62%
    using vi = vector<int>;
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        if (!n) return -1;
        vi tot(n + 1, 0);
        partial_sum(begin(nums), end(nums), begin(tot) + 1);
        FOR(i,n) if (tot[i] - tot[0] == tot[n] - tot[i + 1]) return i;
        return -1;
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
