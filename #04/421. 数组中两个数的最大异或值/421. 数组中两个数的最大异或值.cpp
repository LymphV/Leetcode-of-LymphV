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
给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。

进阶：你可以在 O(n) 的时间解决这个问题吗？

 

示例 1：

输入：nums = [3,10,5,25,2,8]
输出：28
解释：最大运算结果是 5 XOR 25 = 28.
示例 2：

输入：nums = [0]
输出：0
示例 3：

输入：nums = [2,4]
输出：6
示例 4：

输入：nums = [8,10,2]
输出：10
示例 5：

输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
输出：127
 

提示：

1 <= nums.length <= 2 * 104
0 <= nums[i] <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///228ms 11.60% 60.6M 5.10%
    using vi = vector<int>;
    using vii = vector<vi>;

    struct Trie
    {
        static const int N = 32;
        vii data;

        Trie () : data(1, vi{-1, -1}) {}

        void add (int x)
        {
            int now = 0;
            FOR(i,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                if (data[now][t] < 0)
                {
                    data[now][t] = data.size();
                    data.emplace_back(vi{-1, -1});
                }
                now = data[now][t];
            }
        }

        int check (int x)
        {
            int now = 0;
            int rst = 0;
            FOR(i,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                rst <<= 1;
                if (0 < data[now][1 ^ t])
                {
                    now = data[now][1 ^ t];
                    rst |= 1;
                }
                else now = data[now][t];
            }
            return rst;
        }
    };

public:
    int findMaximumXOR(vector<int>& nums) {
        int rst = 0;

        Trie trie;
        for (int x : nums)
        {
            trie.add(x);
            rst = max(rst, trie.check(x));
        }
        return rst;
    }
};


class SolutionV2 {///220ms 12.90% 60.7M 5.10%
    using b32 = bitset<32>;
    using vi = vector<int>;
    using vii = vector<vi>;

    struct Trie
    {
        static const int N = 32;
        vii data;

        Trie () : data(1, vi{-1, -1}) {}

        void add (int x)
        {
            int now = 0;
            FOR(i,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                if (data[now][t] < 0)
                {
                    data[now][t] = data.size();
                    data.emplace_back(vi{-1, -1});
                }
                now = data[now][t];
            }
        }

        int check (int x)
        {
            int now = 0;
            int rst = 0;
            FOR(i,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                rst <<= 1;
                if (0 < data[now][1 ^ t])
                {
                    now = data[now][1 ^ t];
                    rst |= 1;
                }
                else now = data[now][t];
            }
            return rst;
        }
    };

public:
    int findMaximumXOR(vector<int>& nums) {
        int rst = 0;

        Trie trie;
        for (int x : nums) trie.add(x);
        for (int x : nums) rst = max(rst, trie.check(x));
        return rst;
    }
};


class SolutionV1 {///228ms 11.60% 43.1M 18.4%
    using b32 = bitset<32>;
    int N = 32;
public:
    int findMaximumXOR(vector<int>& nums) {
        int rst = 0;
        FOR(i,N)
        {
            rst <<= 1;
            int n = N - i - 1;
            unordered_set<int> s;
            for (int x : nums)
                s.insert(x >> n);

            int t = rst | 1;
            for (int x : nums)
            {
                if (s.count((x >> n) ^ t))
                {
                    rst = t;
                    break;
                }
            }
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {2,4},
    };
    for (auto & x : xs)
        print(x), print(Solution().findMaximumXOR(x)), print("===");
    return 0;
}
#endif
