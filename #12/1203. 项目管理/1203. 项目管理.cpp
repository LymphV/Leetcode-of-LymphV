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
公司共有 n 个项目和  m 个小组，每个项目要不无人接手，要不就由 m 个小组之一负责。

group[i] 表示第 i 个项目所属的小组，如果这个项目目前无人接手，那么 group[i] 就等于 -1。（项目和小组都是从零开始编号的）小组可能存在没有接手任何项目的情况。

请你帮忙按要求安排这些项目的进度，并返回排序后的项目列表：

同一小组的项目，排序后在列表中彼此相邻。
项目之间存在一定的依赖关系，我们用一个列表 beforeItems 来表示，其中 beforeItems[i] 表示在进行第 i 个项目前（位于第 i 个项目左侧）应该完成的所有项目。
如果存在多个解决方案，只需要返回其中任意一个即可。如果没有合适的解决方案，就请返回一个 空列表 。

 

示例 1：



输入：n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
输出：[6,3,4,1,5,2,0,7]
示例 2：

输入：n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
输出：[]
解释：与示例 1 大致相同，但是在排序后的列表中，4 必须放在 6 的前面。
 

提示：

1 <= m <= n <= 3 * 104
group.length == beforeItems.length == n
-1 <= group[i] <= m - 1
0 <= beforeItems[i].length <= n - 1
0 <= beforeItems[i][j] <= n - 1
i != beforeItems[i][j]
beforeItems[i] 不含重复元素

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-items-by-groups-respecting-dependencies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

void printq(queue<int> q)
{
    vi rst;
    while (!q.empty()) rst.emplace_back(q.front()), q.pop();
    print(rst);
}

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///280ms 51.51% 94.6M 19.51%
    using vi = vector<int>;
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        if (!n) return {};
        vi in(n, 0), gin(m, 0), rst;
        vector<vi> out(n, vi{});
        vector<queue<int>> ready(n, queue<int>());
        queue<int> gready, oready;///group ready, -1 ready
        FOR(i,n) for(int j : beforeItems[i])
        {
            ++in[i], out[j].emplace_back(i);
            if (group[i] != group[j] && 0 <= group[i]) ++gin[group[i]];
        }

        FOR(i,m) if (!gin[i]) gready.push(i);
        FOR(i,n) if (!in[i]) ~group[i] ? ready[group[i]].push(i) : oready.push(i);
        auto addPoint = [&] (queue<int> & q)
        {
            while (!q.empty())
            {
                int next = q.front(); q.pop();
                rst.emplace_back(next);
                for (int x : out[next])
                {
                    if (!--in[x]) ~group[x] ? ready[group[x]].push(x) : oready.push(x);
                    if (~group[x] && group[x] != group[next])
                    {
                        if (!--gin[group[x]]) gready.push(group[x]);
                    }
                }
            }
        };


        for (int now = -1; rst.size() < n; now = -1)
        {
            addPoint(oready);
            if (rst.size() == n) break;
            if (gready.empty()) return {};

            now = gready.front(); gready.pop();
            while (ready[now].empty() &&  !gready.empty())
            {
                now = gready.front(); gready.pop();
            }
            if (ready[now].empty()) return {};

            addPoint(ready[now]);
        }
        return rst;
    }
};


class SolutionV1 {///232ms 72.73% 67.5M 48.78%
    using vi = vector<int>;
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        if (!n) return {};
        vi in(n, 0), gin(m, 0), rst;
        vector<vi> out(n, vi{});
        unordered_map<int,queue<int>> ready;
        queue<int> gready;
        FOR(i,n) for(int j : beforeItems[i])
        {
            ++in[i], out[j].emplace_back(i);
            if (group[i] != group[j] && 0 <= group[i]) ++gin[group[i]];
        }

        FOR(i,n) if (!in[i]) ready[group[i]].push(i);
        FOR(i,m) if (!gin[i]) gready.push(i);


        for (int now = -1; rst.size() < n; )
        {

            auto it = ready.find(now);
            if (it == end(ready) || it->second.empty())
            {
                now = -1;
                it = ready.find(now);
                while ((it == end(ready) || it->second.empty()) && !gready.empty())
                {
                    now = gready.front(); gready.pop();
                    it = ready.find(now);
                }
            }
            if ((it == end(ready) || it->second.empty()) && gready.empty()) return {};

            int k = it->first;
            auto & v = it->second;

            now = k;
            int next = v.front(); v.pop();
            rst.emplace_back(next);

            for (int x : out[next])
            {
                if (!--in[x]) ready[group[x]].push(x);
                if (group[next] != group[x] && 0 <= group[x])
                {
                    if (!--gin[group[x]]) gready.push(group[x]);
                }
            }
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<vector<vi>, vector<vi>>> xs{
        {
            {{8,2}, {-1,-1,1,0,0,1,0,-1}},
            {
                {},{6},{5},{6},{3,6},{},{},{}
            }
        },
        {
            {{10,4},{0,1,1,2,3,-1,0,0,0,1}},
            {
                {2,5},{3,5,4,6,8,7,2},{7},{},{},{},{},{},{},{}
            }
        }
    };
    for (auto & [x,y] : xs)
        print(x, y), print(Solution().sortItems(x[0][0],x[0][1],x[1], y)), print("===");
    return 0;
}
#endif
