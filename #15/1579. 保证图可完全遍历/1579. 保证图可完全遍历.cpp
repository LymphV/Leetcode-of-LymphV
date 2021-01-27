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
Alice 和 Bob 共有一个无向图，其中包含 n 个节点和 3  种类型的边：

类型 1：只能由 Alice 遍历。
类型 2：只能由 Bob 遍历。
类型 3：Alice 和 Bob 都可以遍历。
给你一个数组 edges ，其中 edges[i] = [typei, ui, vi] 表示节点 ui 和 vi 之间存在类型为 typei 的双向边。请你在保证图仍能够被 Alice和 Bob 完全遍历的前提下，找出可以删除的最大边数。如果从任何节点开始，Alice 和 Bob 都可以到达所有其他节点，则认为图是可以完全遍历的。

返回可以删除的最大边数，如果 Alice 和 Bob 无法完全遍历图，则返回 -1 。

 

示例 1：



输入：n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
输出：2
解释：如果删除 [1,1,2] 和 [1,1,3] 这两条边，Alice 和 Bob 仍然可以完全遍历这个图。再删除任何其他的边都无法保证图可以完全遍历。所以可以删除的最大边数是 2 。
示例 2：



输入：n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
输出：0
解释：注意，删除任何一条边都会使 Alice 和 Bob 无法完全遍历这个图。
示例 3：



输入：n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
输出：-1
解释：在当前图中，Alice 无法从其他节点到达节点 4 。类似地，Bob 也不能达到节点 1 。因此，图无法完全遍历。
 

提示：

1 <= n <= 10^5
1 <= edges.length <= min(10^5, 3 * n * (n-1) / 2)
edges[i].length == 3
1 <= edges[i][0] <= 3
1 <= edges[i][1] < edges[i][2] <= n
所有元组 (typei, ui, vi) 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///548ms 92.42% 135.7M 46.97%
    using vi = vector<int>;

    class UFSet
    {
        vi father, level;
    public:
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
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UFSet ufsa(n), ufsb(n);
        int cnta = 0, m = edges.size();
        for (vi & e : edges) if (e[0] == 3 && !ufsa.same(e[1] - 1, e[2] - 1))
        {
             ++cnta;
             ufsa.unite(e[1] - 1, e[2] - 1);
             ufsb.unite(e[1] - 1, e[2] - 1);
        }
        int cntb = cnta, rst = cnta;
        if (rst == n - 1) return m - rst;
        for (vi & e : edges) if (e[0] == 1 && !ufsa.same(e[1] - 1, e[2] - 1))
        {
            ++rst;
            if (++cnta == n - 1) break;
            ufsa.unite(e[1] - 1, e[2] - 1);
        }
        for (vi & e : edges) if (e[0] == 2 && !ufsb.same(e[1] - 1, e[2] - 1))
        {
            ++rst;
            if (++cntb == n - 1) break;
            ufsb.unite(e[1] - 1, e[2] - 1);
        }
        return cnta == n - 1 && cntb == n - 1 ? m - rst : -1;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<int,vector<vi>>> xs{
        {
            19,
            {{1,1,2},{2,1,2},{1,2,3},{2,2,3},{1,1,4},{2,1,4},{1,1,5},{2,1,5},{3,4,6},{3,3,7},{1,2,8},{2,2,8},{3,1,9},{1,3,10},{2,3,10},{1,8,11},{2,8,11},{1,5,12},{2,5,12},{1,8,13},{2,8,13},{3,10,14},{1,9,15},{2,9,15},{3,13,16},{3,9,17},{3,11,18},{1,1,19},{2,1,19},{2,4,10},{2,2,4},{2,3,18},{2,14,15},{1,4,17},{1,7,10},{1,6,14},{1,3,12},{1,5,14}}
        }
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().maxNumEdgesToRemove(x, y)), print("===");
    return 0;
}
#endif
