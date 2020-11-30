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
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 91.02% 9.2M 13.08%
public:
    void moveZeroes(vector<int>& nums) {
        for (auto i = begin(nums), j = begin(nums); j != end(nums); ++j)
            if (*j) swap(*(i++), *j);
    }
};


class SolutionV1 {///8ms 91.02% 9.1M 21.60%
public:
    void moveZeroes(vector<int>& nums) {
        for (auto i = begin(nums), j = begin(nums); i != end(nums); ++i)
        {
            if (j == end(nums)) *i = 0;
            else
            {
                while (j != end(nums) && !*j) ++j;
                if (j != end(nums)) *i = *(j++);
                else *i = 0;
            }
        }
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {0,1,0},
        {0}
    };
    for (auto x : xs)
        print(x), (Solution().moveZeroes(x)), print(x), print("===");
    return 0;
}
#endif
