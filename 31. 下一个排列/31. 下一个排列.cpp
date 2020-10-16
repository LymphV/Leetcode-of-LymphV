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
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///16ms 26.17% 12.2M 12.3%
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n - 1;
        for (; 0 < k && nums[k] <= nums[k - 1]; --k);
        --k;
        for (int i = k + 1, j = n - 1; i < j; ++i, --j)
            swap(nums[i],nums[j]);
        if (~k)
        {
            int m = upper_bound(begin(nums) + k + 1, end(nums), nums[k]) - begin(nums);
            swap(nums[m], nums[k]);
        }
    }
};


///库函数
class SolutionV1 {///8ms 66.00% 12.2M 5.23%
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(begin(nums),end(nums));
    }
};


#if defined(LocalLymphV)
int main()
{
    /*vi a {1,2,3,4};
    do
    {
        print(a);
    }while (next_permutation(begin(a), end(a)));*/

    vector<vi> xs{
        {1,3,2,4},
        {3,2,1},
        {1},
        {1,2},
        {1,5,1,1},
        {1,2,3}
    };
    for (auto x : xs)
        print(x), Solution().nextPermutation(x), print(x), print("===");
    return 0;
}
#endif
