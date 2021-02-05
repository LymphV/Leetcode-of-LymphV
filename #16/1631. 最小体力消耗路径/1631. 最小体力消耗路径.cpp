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
你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子 (row, col) 的高度。一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。

一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。

请你返回从左上角走到右下角的最小 体力消耗值 。

 

示例 1：



输入：heights = [[1,2,2],[3,8,2],[5,3,5]]
输出：2
解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。
示例 2：



输入：heights = [[1,2,3],[3,8,4],[5,3,5]]
输出：1
解释：路径 [1,2,3,4,5] 的相邻格子差值绝对值最大为 1 ，比路径 [1,3,5,3,5] 更优。
示例 3：


输入：heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
输出：0
解释：上图所示路径不需要消耗任何体力。
 

提示：

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 10^6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-with-minimum-effort
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///
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
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        int stop = n * m - 1;
        UFSet ufs(n * m);
        vector<vi> es;
        FOR(i,n)ffor(j,1,m)es.emplace_back(vi{abs(heights[i][j] - heights[i][j - 1]), i * m + j, i * m + j - 1});
        FOR(j,m)ffor(i,1,n)es.emplace_back(vi{abs(heights[i][j] - heights[i - 1][j]), i * m + j, (i - 1) * m + j});
        sort(begin(es), end(es));
        for (vi & e : es)
        {
            ufs.unite(e[1], e[2]);
            if (ufs.same(0, stop)) return e[0];
        }
        return 0;
    }
};


class SolutionV3 {///124ms 99.85% 17.9M 89.96%
    using pii = pair<int,int>;
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        const int dir[][2]{{0,1},{0,-1},{1,0},{-1,0}};
        int n = heights.size(), m = heights[0].size();
        priority_queue<pii> pq;
        pq.push(pii{0,((0 << 8) | (0 << 16) | (4 << 24))});
        while (!pq.empty())
        {
            auto [a, b] = pq.top(); pq.pop();
            unsigned char * v = (unsigned char*)&b;
            if (v[1] == n - 1 && v[2] == m - 1) return -a;
            if (heights[v[1]][v[2]] == -1) continue;
            int h = heights[v[1]][v[2]];
            heights[v[1]][v[2]] = -1;
            FOR(i,4)if((i ^ 1) != v[3])
            {
                int x = v[1] + dir[i][0], y = v[2] + dir[i][1];
                if (x < 0 || n <= x || y < 0 || m <= y || heights[x][y] == -1) continue;
                pq.push(pii{min(a, -abs(h - heights[x][y])), ((x << 8) | (y << 16) | (i << 24))});
            }
        }
        return 0;
    }
};

class SolutionV2 {///136ms 99.75% 18M 89.70%
    using vi = vector<int>;
    using pii = pair<int,int>;
    const vector<vi> dir{{0,1},{0,-1},{1,0},{-1,0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        priority_queue<pii> pq;
        pq.push(pii{0,((0 << 8) | (0 << 16) | (4 << 24))});
        while (!pq.empty())
        {
            auto [a, b] = pq.top(); pq.pop();
            unsigned char * v = (unsigned char*)&b;
            if (v[1] == n - 1 && v[2] == m - 1) return -a;
            if (heights[v[1]][v[2]] == -1) continue;
            int h = heights[v[1]][v[2]];
            heights[v[1]][v[2]] = -1;
            FOR(i,4)if((i ^ 1) != v[3])
            {
                int x = v[1] + dir[i][0], y = v[2] + dir[i][1];
                if (x < 0 || n <= x || y < 0 || m <= y || heights[x][y] == -1) continue;
                pq.push(pii{min(a, -abs(h - heights[x][y])), ((x << 8) | (y << 16) | (i << 24))});
            }
        }
        return 0;
    }
};

class SolutionV1 {///412ms 79.29% 35.7M 36.55%
    using vi = vector<int>;
    const vector<vi> dir{{0,1},{0,-1},{1,0},{-1,0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        priority_queue<vi> pq;
        pq.push(vi{0,0,0,-1});
        while (!pq.empty())
        {
            vi v = pq.top(); pq.pop();
            if (v[1] == n - 1 && v[2] == m - 1) return -v[0];
            if (heights[v[1]][v[2]] == -1) continue;
            int h = heights[v[1]][v[2]];
            heights[v[1]][v[2]] = -1;
            FOR(i,4)if((i ^ 1) != v[3])
            {
                int x = v[1] + dir[i][0], y = v[2] + dir[i][1];
                if (x < 0 || n <= x || y < 0 || m <= y || heights[x][y] == -1) continue;
                pq.push(vi{min(v[0], -abs(h - heights[x][y])), x, y, i});
            }
        }
        return 0;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{1,2,2},{3,8,2},{5,3,5}},
        {{1,10,6,7,9,10,4,9}}

    };
    for (auto & x : xs)
        print(x), print(Solution().minimumEffortPath(x)), print("===");
    return 0;
}
#endif
