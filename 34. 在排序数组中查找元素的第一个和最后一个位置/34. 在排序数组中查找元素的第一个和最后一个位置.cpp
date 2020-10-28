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
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
通过次数140,927提交次数348,093

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///20ms 76.52% 13.8M 5.03%
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto start = begin(nums), stop = end(nums);
        auto low = lower_bound(start, stop, target), up = upper_bound(start, stop, target);
        if (low == up) return {-1, -1};
        return {int(low - start), int(up - start) - 1};
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {
            {5,7,7,8,8,10},8
        }
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().searchRange(x,y)), print("===");
    return 0;
}
#endif
