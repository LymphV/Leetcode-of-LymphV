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
n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。

如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头。

给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置，返回 可以移除的石子 的最大数量。

 

示例 1：

输入：stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出：5
解释：一种移除 5 块石头的方法如下所示：
1. 移除石头 [2,2] ，因为它和 [2,1] 同行。
2. 移除石头 [2,1] ，因为它和 [0,1] 同列。
3. 移除石头 [1,2] ，因为它和 [1,0] 同行。
4. 移除石头 [1,0] ，因为它和 [0,0] 同列。
5. 移除石头 [0,1] ，因为它和 [0,0] 同行。
石头 [0,0] 不能移除，因为它没有与另一块石头同行/列。
示例 2：

输入：stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
输出：3
解释：一种移除 3 块石头的方法如下所示：
1. 移除石头 [2,2] ，因为它和 [2,0] 同行。
2. 移除石头 [2,0] ，因为它和 [0,0] 同列。
3. 移除石头 [0,2] ，因为它和 [0,0] 同行。
石头 [0,0] 和 [1,1] 不能移除，因为它们没有与另一块石头同行/列。
示例 3：

输入：stones = [[0,0]]
输出：0
解释：[0,0] 是平面上唯一一块石头，所以不可以移除它。
 

提示：

1 <= stones.length <= 1000
0 <= xi, yi <= 104
不会有两块石头放在同一个坐标点上

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///44ms 99.50% 18.7M 38.88%
    using vi = vector<int>;
    class UFSet
    {
    public:
        unordered_map<int,int> father, level;
        int find (int i)
        {
            if (!father.count(i)) return father[i] = i;
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        vi row(10001, -1);
        UFSet ufs;
        for (auto & x : stones)
        {
            if (!~row[x[0]]) ufs.find(row[x[0]] = x[1]);
            else ufs.unite(x[1], row[x[0]]);
        }
        int rst = stones.size();
        for (auto & [x , y] : ufs.father) if (ufs.find(x) == x) --rst;
        return rst;
    }
};

class SolutionV3 {///44ms 99.50% 16.8M 47.47%
    using vi = vector<int>;
    class UFSet
    {
    public:
        unordered_map<int,int> father, level;
        int find (int i)
        {
            if (!father.count(i)) return father[i] = i;
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int,int> row;
        UFSet ufs;
        for (auto & x : stones)
        {
            if (!row.count(x[0])) ufs.find(row[x[0]] = x[1]);
            else ufs.unite(x[1], row[x[0]]);
        }
        int rst = stones.size();
        for (auto & [x , y] : ufs.father) if (ufs.find(x) == x) --rst;
        return rst;
    }
};

class SolutionV2 {///36ms 100.00% 16.4M 48.99%
    using vi = vector<int>;
    class UFSet
    {
    public:
        vi father, level;
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
        }
        int find (int i)
        {
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int,int> row, col;
        for (auto & x : stones)
            if (!col.count(x[1])) col[x[1]] = col.size();
        int m = row.size(), n = col.size();
        UFSet ufs(n);
        for (auto & x : stones)
        {
            if (!row.count(x[0])) row[x[0]] = col[x[1]];
            else ufs.unite(col[x[1]], row[x[0]]);
        }
        int rst = stones.size();
        for (auto & [x, y] : col) if (ufs.find(y) == y) --rst;
        return rst;
    }
};

class SolutionV1 {///44ms 99.50% 16.3M 49.49%
    using vi = vector<int>;
    class UFSet
    {
    public:
        vi father, level;
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
        }
        int find (int i)
        {
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int,int> row, col;
        for (auto & x : stones)
        {
            row[x[0]] = -1;
            if (!col.count(x[1])) col[x[1]] = col.size();
        }
        int m = row.size(), n = col.size();
        UFSet ufs(n);
        for (auto & x : stones)
        {
            if (!~row[x[0]]) row[x[0]] = col[x[1]];
            else ufs.unite(col[x[1]], row[x[0]]);
        }
        int rst = stones.size();
        for (auto & [x, y] : col) if (ufs.find(y) == y) --rst;
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}},
        {{0,0},{0,2},{1,1},{2,0},{2,2}}
    };
    for (auto & x : xs)
        print(x), print(Solution().removeStones(x)), print("===");
    return 0;
}
#endif
