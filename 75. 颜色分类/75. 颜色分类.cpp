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
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]
进阶：

一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution { ///0ms 100.00% 8.4M 9.66%
public:
    void sortColors(vector<int>& nums) {
        int le = -1, ri = nums.size();
        for (int i = 0; i < ri; ++i)
            if (!nums[i]) swap(nums[++le], nums[i]);
            else if (nums[i] == 2) swap(nums[--ri], nums[i--]);
    }
};

class SolutionV1 { ///4ms 57.70% 8M 97.59%
public:
    void sortColors(vector<int>& nums) {
        int cnt[3]{0,0,0};
        for (int x : nums) ++cnt[x];
        for (int i = 0, j = 0; i < 3; ++i)
            while(cnt[i]--) nums[j++] = i;
    }
};




#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {},
        {2},
        {2,0,2,1,1,0}
    };
    for (auto x : xs)
        print(x), Solution().sortColors(x), print(x), print("===");
    return 0;
}
#endif
