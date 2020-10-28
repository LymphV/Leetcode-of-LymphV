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
我们把数组 A 中符合下列属性的任意连续子数组 B 称为 “山脉”：

B.length >= 3
存在 0 < i < B.length - 1 使得 B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
（注意：B 可以是 A 的任意子数组，包括整个数组 A。）

给出一个整数数组 A，返回最长 “山脉” 的长度。

如果不含有 “山脉” 则返回 0。

 

示例 1：

输入：[2,1,4,7,3,2,5]
输出：5
解释：最长的 “山脉” 是 [1,4,7,3,2]，长度为 5。
示例 2：

输入：[2,2,2]
输出：0
解释：不含 “山脉”。
 

提示：

0 <= A.length <= 10000
0 <= A[i] <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-mountain-in-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///32ms 99.22% 18.5M 14.29%
public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        if (!n) return 0;
        int rst = 0;
        int now = 0;
        int up = 0;
        ffor(i,1,n)
        {
            if (!up)
            {
                if (A[i] == A[i - 1]);
                else if (A[i] < A[i - 1]) ;
                else now = 2, up = 1;
            }
            else if (0 < up)
            {
                if (A[i] == A[i - 1]) now = up = 0;
                else if (A[i] < A[i - 1]) up = -1, rst = max(++now, rst);
                else ++now;
            }
            else
            {
                if (A[i] == A[i - 1]) now = up = 0;
                else if (A[i] < A[i - 1]) rst = max(++now, rst);
                else now = 2, up = 1;
            }
        }
        return rst;
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
