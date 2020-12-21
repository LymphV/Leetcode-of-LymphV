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
给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

 

示例 1：

输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。
示例 2：

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。
示例 3：

输入：digits = [0]
输出：[1]
 

提示：

1 <= digits.length <= 100
0 <= digits[i] <= 9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/plus-one
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 8.8M 60.88%
    using vi = vector<int>;
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1, carry = 1; carry; --i)
        {
            if (i < 0)
            {

                vi rst(digits.size() + 1, 0);
                rst[0] = 1;
                return rst;
            }
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        return digits;
    }
};


class SolutionV2 {///4ms 62.52% 9.1M 6.86%
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1, carry = 1; carry; --i)
        {
            if (i < 0)
            {
                digits.insert(begin(digits), 1);
                break;
            }
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        return digits;
    }
};

class SolutionV1 {///4ms 62.52% 9.1M 7.19%
    using vi = vector<int>;
public:
    vector<int> plusOne(vector<int>& digits) {
        vi rst(rbegin(digits), rend(digits));
        for (int i = 0, n = rst.size(), carry = 1; carry; ++i)
        {
            if (n <= i) rst.emplace_back(0);
            rst[i] += carry;
            carry = rst[i] / 10;
            rst[i] %= 10;
        }
        return {rbegin(rst), rend(rst)};
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,2,3}
    };
    for (auto x : xs)
        print(x), print(Solution().plusOne(x)), print("===");
    return 0;
}
#endif
