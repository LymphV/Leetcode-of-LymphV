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
已知存在一个按非降序排列的整数数组 nums ，数组中的值不必互不相同。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转 ，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,4,4,5,6,6,7] 在下标 5 处经旋转后可能变为 [4,5,6,6,7,0,1,2,4,4] 。

给你 旋转后 的数组 nums 和一个整数 target ，请你编写一个函数来判断给定的目标值是否存在于数组中。如果 nums 中存在这个目标值 target ，则返回 true ，否则返回 false 。

 

示例 1：

输入：nums = [2,5,6,0,0,1,2], target = 0
输出：true
示例 2：

输入：nums = [2,5,6,0,0,1,2], target = 3
输出：false
 

提示：

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
题目数据保证 nums 在预先未知的某个下标上进行了旋转
-104 <= target <= 104
 

进阶：

这是 搜索旋转排序数组 的延伸题目，本题中的 nums  可能包含重复元素。
这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///8ms 60.01% 13.7M 30.35%
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return 0;
        for (int i = 0, j = n; i < j;)
        {
            if (nums[i] == target || nums[j - 1] == target) return 1;
            int k = (i + j) / 2;
            if (nums[k] == target) return 1;

            if (nums[i] == nums[j - 1] && nums[i] == nums[k]) ++i, --j;
            else if (nums[i] < target)
            {
                if (nums[k] < target && nums[i] <= nums[k]) i = k + 1;
                else j = k;
            }
            else if (target < nums[j - 1])
            {
                if (target < nums[k] && nums[k] <= nums[j - 1]) j = k;
                else i = k + 1;
            }
            else return 0;
        }
        return 0;
    }
};

class SolutionV1 {///WA
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return 0;
        for (int i = 0, j = n; i < j;)
        {
            if (nums[i] == target || nums[j - 1] == target) return 1;
            int k = (i + j) / 2;
            if (nums[k] == target) return 1;
            if (nums[i] < target)
            {
                if (nums[k] < target) i = k + 1;
                else j = k;
            }
            else if (target < nums[j - 1])
            {
                if (target < nums[k]) j = k;
                else i = k + 1;
            }
        }
        return 0;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{{{1}, 0},
        {{1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},2},
        {{4,5,6,7,0,1,2,},0}
    };
    for (auto &[x, y] : xs)
        print(x,y), print(Solution().search(x,y)), print("===");
    return 0;
}
#endif
