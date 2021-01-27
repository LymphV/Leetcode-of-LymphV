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
给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。

连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。

 

示例 1：

输入：nums = [1,3,5,4,7]
输出：3
解释：最长连续递增序列是 [1,3,5], 长度为3。
尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。
示例 2：

输入：nums = [2,2,2,2,2]
输出：1
解释：最长连续递增序列是 [2], 长度为1。
 

提示：

0 <= nums.length <= 104
-109 <= nums[i] <= 109
通过次数57,415提交次数122,274

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 99.62% 10.5M 100.00%
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        int rst = 1, last = nums[0], cnt = 1;
        ffor(i,1,n)
        {
            if (last < nums[i]) rst = max(rst, ++cnt);
            else cnt = 1;
            last = nums[i];
        }
        return rst;
    }
};

class SolutionV1 {///12ms 96.64% 10.7M 95.75%
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        int rst = 1, last = nums[0], cnt = 1;
        for (int x : nums)
        {
            if (last < x) rst = max(rst, ++cnt);
            else cnt = 1;
            last = x;
        }
        return rst;
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
