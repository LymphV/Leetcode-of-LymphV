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
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。

连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。

请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。

 

示例 1：



输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：

我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
注意到任意两个点之间只有唯一一条路径互相到达。
示例 2：

输入：points = [[3,12],[-2,5],[-4,1]]
输出：18
示例 3：

输入：points = [[0,0],[1,1],[1,0],[-1,1]]
输出：4
示例 4：

输入：points = [[-1000000,-1000000],[1000000,1000000]]
输出：4000000
示例 5：

输入：points = [[0,0]]
输出：0
 

提示：

1 <= points.length <= 1000
-106 <= xi, yi <= 106
所有点 (xi, yi) 两两不同。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/min-cost-to-connect-all-points
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


///Prim+Heap
class Solution {///164ms 86.45% 41.3M 60.05%
    using vi = vector<int>;
    using pii = pair<int,int>;

    int dis (vi & a, vi & b)
    {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vi vst(n, 0);
        int cnt = 0, rst = 0;
        priority_queue<pii> pq;
        pq.push(pii(0, 0));

        while (!pq.empty())
        {
            auto [d, i] = pq.top(); pq.pop();
            if (vst[i]) continue;
            vst[i] = 1, ++cnt, rst -= d;
            if (cnt == n) break;
            FOR(j,n)if (!vst[j]) pq.push(pii(-dis(points[i],points[j]),j));
        }
        return rst;
    }
};


///Kruskal
class SolutionV1 {///1940ms 5.15% 171.8M 6.79%
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

    int dis (vi & a, vi & b)
    {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vi> ds;
        FOR(i,n)FOR(j,i) ds.emplace_back(vi{dis(points[i], points[j]),i,j});
        sort (begin(ds), end(ds));
        UFSet ufs(n);
        int rst = 0, cnt = 0;
        for (vi & v : ds)
        {
            if (ufs.same(v[1], v[2])) continue;
            rst += v[0], ++cnt;
            if (cnt == n - 1) break;
            ufs.unite(v[1], v[2]);
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{0,0},{2,2},{3,10},{5,2},{7,0}}
    };
    for (auto & x : xs)
        print(x), print(Solution().minCostConnectPoints(x)), print("===");
    return 0;
}
#endif
