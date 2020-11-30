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
给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。

如果数组元素个数小于 2，则返回 0。

示例 1:

输入: [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。
示例 2:

输入: [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0。
说明:

你可以假设数组中所有元素都是非负整数，且数值在 32 位有符号整数范围内。
请尝试在线性时间复杂度和空间复杂度的条件下解决此问题。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-gap
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///12ms 79.22% 8.7M 68.39%
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        sort(begin(nums), end(nums));
        int rst = nums[1] - nums[0];
        ffor(i,1,n) rst = max(rst, nums[i] - nums[i - 1]);
        return rst;
    }
};

class SolutionV1 {///8ms 97.33% 9.1M 21.42%
    using UC = unsigned char;

    /***************
    op[i] 提供类型的第i个字节的比较方式，具体来说有5种取值。
    −1：该字节不是排序的关键字。
    0：以该字节为基准从小到大排序。
    1：以该字节为基准从大到小排序。
    2：以该字节为基准从小到大排序，且该字节的最高位是有符号整形的符号位。
    3：以该字节为基准从大到小排序，且该字节的最高位是有符号整形的符号位。

    例如，对int从小到大排序，则应将{0,0,0,2}传入op。
    **************/
    template<typename T>
    void Radixsort(T * fst, T * lst, T * buf, int * op)
    {
        static int b[0x100];
        int Len = lst - fst, Sz = sizeof(T), at = 0;

        UC * bgn, * end, tmp;
        FOR(i,Sz)
        {
            if (op[i] == -1) continue;
            bgn = (UC*)fst + i;
            end = (UC*)lst + i;

            tmp = ((op[i] & 1) ? 0xff : 0) ^ ((op[i] & 2) ? 0x80 : 0);
            memset(b, 0, sizeof(b));

            for(UC * it = bgn; it != end; it += Sz)
                ++b[tmp ^ *it];

            ffor(j,1,0x100) b[j] += b[j-1];
            for(UC * it = end; it != bgn; buf[--b[tmp ^ *(it -= Sz)]] = *--lst);
            lst = buf + Len;
            swap(fst,buf);
            at^=1;
        }
        if(at)memcpy(buf, fst, Sz * Len);
    }

public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        int op[4] = {0,0,0,2};
        vector<int> buf(n);
        Radixsort (&nums[0], &nums[0] + n, &buf[0], op);
        int rst = nums[1] - nums[0];
        ffor(i,1,n) rst = max(rst, nums[i] - nums[i - 1]);
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {3,6,9,1},
        {10},
        {}
    };
    for (auto x : xs)
        print(x), print(Solution().maximumGap(x)), print("===");
    return 0;
}
#endif
