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
给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c 。

 

示例 1：

输入：c = 5
输出：true
解释：1 * 1 + 2 * 2 = 5
示例 2：

输入：c = 3
输出：false
示例 3：

输入：c = 4
输出：true
示例 4：

输入：c = 2
输出：true
示例 5：

输入：c = 1
输出：true
 

提示：

0 <= c <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-square-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 54.27% 5.6M 93.52%
public:
    bool judgeSquareSum(int c) {
        for (int a = 0; a * a <= c; ++a)
        {
            double b = sqrt(c - a * a);
            if (b < a) break;
            if (int(b) * int(b) == c - a * a) return 1;
        }
        return 0;
    }
};

class SolutionV1 {///4ms 54.27% 6M 5.17%
public:
    bool judgeSquareSum(int c) {
        for (int a = 0; a <= c; ++a)
        {
            double b = sqrt(c - a * a);
            if (b < a) break;
            if (ceil(b) * ceil(b) == c - a * a) return 1;
        }
        return 0;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<int> xs{3,5};
    for (auto x : xs)
        print(x), print(Solution().judgeSquareSum(x)), print("===");
    return 0;
}
#endif
