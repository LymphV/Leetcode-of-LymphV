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
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

 

示例 1：

输入：nums = [2,2,3,2]
输出：3
示例 2：

输入：nums = [0,1,0,1,0,1,99]
输出：99
 

提示：

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
 

进阶：你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-number-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///8ms 74.16 9.2M 73.63%
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int c : nums)
        {
            b = ~a & (b ^ c);
            a = ~b & (a ^ c);
        }
        return b;
    }
};

class SolutionV2 {///8ms 74.16% 9.1M 99.83%
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int c : nums)
        {
            int d = (~a & b & c) | (a & ~b & ~c);
            int e = ~a & (b ^ c);
            a = d, b = e;
        }
        return b;
    }
};

class SolutionV1 {///8ms 74.16% 9.2M 76.44%
    void vAddInt (int * v, int x)
    {
        FOR(i,32)
        {
            v[i] = (v[i] + (x & 1)) % 3;
            x >>= 1;
        }
    }
    int v2int (int * v)
    {
        int rst = 0;
        FOR(i,32) rst |= (v[i] << i);
        return rst;
    }
public:
    int singleNumber(vector<int>& nums) {
        int rst[32];
        MS(rst,0);
        for (int x : nums) vAddInt(rst, x);
        return v2int(rst);
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {2,2,3,2}
    };
    for (auto & x : xs)
        print(x), print(Solution().singleNumber(x)), print("===");
    return 0;
}
#endif
