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
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。

例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。

示例 1:

输入: [1,7,4,9,2,5]
输出: 6
解释: 整个序列均为摆动序列。
示例 2:

输入: [1,17,5,10,13,15,10,5,16,8]
输出: 7
解释: 这个序列包含几个长度为 7 摆动序列，其中一个可为[1,17,10,13,10,16,8]。
示例 3:

输入: [1,2,3,4,5,6,7,8,9]
输出: 2
进阶:
你能否用 O(n) 时间复杂度完成此题?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/wiggle-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///n
class Solution {///0ms 100.00% 7.6M 6.37%
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;

        int up = 1, down = 1;
        ffor(i,1,n)
        {
            if (nums[i - 1] < nums[i]) up = down + 1;
            else if (nums[i] < nums[i - 1]) down = up + 1;
        }
        return max(up, down);
    }
};

///n
class SolutionV2 {///4ms 53.20% 7.5M 24.29%
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;

        int up = 1, down = 1;
        ffor(i,1,n)
        {
            if (nums[i - 1] < nums[i]) up = max(up, down + 1);
            else if (nums[i] < nums[i - 1]) down = max(down , up + 1);
        }
        return max(up, down);
    }
};

///n^2
class SolutionV1 {///176ms 6.40% 18M 5.00%
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;

        vvi a(n, vi{1,1,1});///(允许状态+，允许状态-，长度)

        int rst = 1;
        ffor(i,1,n)
        {
            vi & state = a[i];
            FOR(j,i)
            {
                int dif = nums[i] - nums[j];
                if (!dif) continue;
                auto & st = a[j];
                if (st[2] + 1 < state[2] || dif < 0 && !st[1] || 0 < dif && !st[0]) continue;
                if (state[2] < st[2] + 1)state = vi{0,0,st[2] + 1};
                if (dif < 0) state[0] = 1;
                else state[1] = 1;
            }
            rst = max(rst, state[2]);
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,7,4,9,2,5},
        {1,17,5,10,13,15,10,5,16,8},
        {1,2,3,4,5,6,7,8,9},
        {0,0},
        {}
    };
    for (auto x : xs)
        print(x), print(Solution().wiggleMaxLength(x)), print("===");
    return 0;
}
#endif
