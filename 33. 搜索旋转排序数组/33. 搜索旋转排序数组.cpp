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
给你一个升序排列的整数数组 nums ，和一个整数 target 。

假设按照升序排序的数组在预先未知的某个点上进行了旋转。（例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] ）。

请你在数组中搜索 target ，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

 
示例 1：

输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
示例 2：

输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
示例 3：

输入：nums = [1], target = 0
输出：-1
 

提示：

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums 中的每个值都 独一无二
nums 肯定会在某个点上旋转
-10^4 <= target <= 10^4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 81.54% 11.3M 5.04%
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return -1;
        int k;
        for (int i = 0, j = n; i < j;)
        {
            k = (i + j) / 2;
            if (nums[k] == target) return k;
            if (nums[i] <= nums[k])
            {
                if (nums[i] <= target && target < nums[k]) j = k;
                else if (nums[j - 1] < target && target < nums[i]) return -1;
                else i = k + 1;
            }
            else
            {
                if (nums[k] < target && target <= nums[j - 1]) i = k + 1;
                else if (nums[j - 1] < target && target < nums[i]) return -1;
                else j = k;
            }

        }
        return -1;
    }
};


class SolutionV1 {///4ms 81.54% 11.3M 5.04%
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) return -1;
        int k = (n - 1) / 2;
        for (int i = 0, j = n; i < j - 1;)
        {
            if (nums[0] <= nums[k]) i = k + 1;
            else j = k + 1;
            k = (i + j - 1) / 2; print(i,j,k);
        }
        print(k);
        auto start = begin(nums), stop = end(nums);
        auto rst = lower_bound(start, start + k, target);
        if (rst == stop || *rst != target)
            rst = lower_bound(start + k, stop, target);
        if (rst == stop || *rst != target) return -1;
        return rst - start;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{1},0},
        {{3,1},1},
        {{4,5,6,7,0,1,2},3},
        {{4,5,6,7,0,1,2},0}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().search(x,y)), print("===");
    return 0;
}
#endif
