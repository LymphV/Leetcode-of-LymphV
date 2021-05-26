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
给你一个由非负整数组成的数组 nums 。另有一个查询数组 queries ，其中 queries[i] = [xi, mi] 。

第 i 个查询的答案是 xi 和任何 nums 数组中不超过 mi 的元素按位异或（XOR）得到的最大值。换句话说，答案是 max(nums[j] XOR xi) ，其中所有 j 均满足 nums[j] <= mi 。如果 nums 中的所有元素都大于 mi，最终答案就是 -1 。

返回一个整数数组 answer 作为查询的答案，其中 answer.length == queries.length 且 answer[i] 是第 i 个查询的答案。

 

示例 1：

输入：nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
输出：[3,3,7]
解释：
1) 0 和 1 是仅有的两个不超过 1 的整数。0 XOR 3 = 3 而 1 XOR 3 = 2 。二者中的更大值是 3 。
2) 1 XOR 2 = 3.
3) 5 XOR 2 = 7.
示例 2：

输入：nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
输出：[15,-1,5]
 

提示：

1 <= nums.length, queries.length <= 105
queries[i].length == 2
0 <= nums[j], xi, mi <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///TLE
    using vi = vector<int>;
    using vii = vector<vi>;

    struct Trie
    {
        static const int N = 32;
        vii data;

        Trie () : data(1, vi{-1, -1, INT_MAX}) {}

        void add (int x)
        {
            int now = 0;
            ffor(i,2,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                if (data[now][t] < 0)
                {
                    data[now][t] = data.size();
                    data.emplace_back(vi{-1, -1, x});
                }
                data[now][2] = min(data[now][2], x);
                now = data[now][t];
            }
        }
        int check (int x, int ceil, int now = 0, int rst = 0, int i = 2)
        {
            if (ceil < data[now][2]) return -1;
            if (ceil == data[now][2]) return x ^ ceil;

            ffor(i,2,N)
            {
                int n = N - i - 1;
                int t = (x >> n) & 1;
                rst <<= 1;

                if (0 < data[now][1 ^ t] && data[data[now][1 ^ t]][2] <= ceil)
                    rst |= 1, t ^= 1;
                now = data[now][t];
            }
            return rst;
        }
    };
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie t;
        for (int x : nums) t.add(x);
        vi rst;
        for (vi & x : queries)
            rst.emplace_back(t.check(x[0], x[1]));
        return rst;
    }
};

class SolutionV3 {///1796ms 5.33% 415.5M 5.12%
    using vi = vector<int>;
    using vii = vector<vi>;

    struct Trie
    {
        static const int N = 32;
        vii data;
        int minV = INT_MAX;

        Trie () : data(1, vi{-1, -1}) {}

        void add (int x)
        {
            int now = 0;
            ffor(i,2,N)
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
            minV = min(minV, x);
        }
        int check (int x, int ceil, int now = 0, int rst = 0, int i = 2, int v = 0)
        {
            if (ceil < minV) return -1;
            if (ceil == minV) return x ^ ceil;
            if (i == N) return rst;
            int n = N - i - 1;
            int t = (x >> n) & 1;
            rst <<= 1, v <<= 1;
            if (((v | 1) << n) <= ceil)
            {
                if (1 ^ t && 0 < data[now][1] || !(1 ^ t) && data[now][0] <= 0)
                {
                    int r = check(x, ceil, data[now][1], rst | (1 ^ t), i + 1, v | 1);
                    if (~r) return r;
                }
            }
            if (0 < data[now][0])
            {
                int r = check(x, ceil, data[now][0], rst | t, i + 1, v);
                if (~r) return r;
            }
            return -1;
        }
    };
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie t;
        for (int x : nums) t.add(x);
        vi rst;
        for (vi & x : queries)
            rst.emplace_back(t.check(x[0], x[1]));
        return rst;
    }
};

class SolutionV2 {///1832ms 5.12% 415.6M 5.12%
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
            ffor(i,2,N)
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
        int check (int x, int ceil, int now = 0, int rst = 0, int i = 2, int v = 0)
        {
            if (i == N) return rst;
            int n = N - i - 1;
            int t = (x >> n) & 1;
            rst <<= 1, v <<= 1;
            if (((v | 1) << n) <= ceil)
            {
                if (1 ^ t && 0 < data[now][1] || !(1 ^ t) && data[now][0] <= 0)
                {
                    int r = check(x, ceil, data[now][1], rst | (1 ^ t), i + 1, v | 1);
                    if (~r) return r;
                }
            }
            if (0 < data[now][0])
            {
                int r = check(x, ceil, data[now][0], rst | t, i + 1, v);
                if (~r) return r;
            }
            return -1;
        }
    };
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie t;
        for (int x : nums) t.add(x);
        vi rst;
        for (vi & x : queries)
            rst.emplace_back(t.check(x[0], x[1]));
        return rst;
    }
};

class SolutionV1 {///1860ms 5.12% 415.7M 5.12%
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
            ffor(i,1,N)
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

        int check (int x, int ceil, int now = 0, int rst = 0, int i = 1, int v = 0)
        {
            if (i == N) return rst;
            int n = N - i - 1;
            int t = (x >> n) & 1;
            rst <<= 1, v <<= 1;
            if (((v | 1) << n) <= ceil)
            {
                if (1 ^ t && 0 < data[now][1] || !(1 ^ t) && data[now][0] <= 0)
                {
                    int r = check(x, ceil, data[now][1], rst | (1 ^ t), i + 1, v | 1);
                    if (~r) return r;
                }
            }
            if (0 < data[now][0])
            {
                int r = check(x, ceil, data[now][0], rst | t, i + 1, v);
                if (~r) return r;
            }
            return -1;
        }
    };
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie t;
        for (int x : nums) t.add(x);
        vi rst;
        for (vi & x : queries)
            rst.emplace_back(t.check(x[0], x[1]));
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi, vector<vi>>> xs{
        //{{0,1,2,3,4}, {{3,1}}}
        //{{0,1,2,3,4}, {{3,1},{1,3},{5,6}}},
        {{5,2,4,6,6,3}, {{12,4},{8,1},{6,3}, {3,2}}}
        //{{5,2,4,6,6,3}, {{8,1}}}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().maximizeXor(x, y)), print("===");
    return 0;
}
#endif
