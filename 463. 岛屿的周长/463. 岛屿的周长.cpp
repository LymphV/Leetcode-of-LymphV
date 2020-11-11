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
给定一个包含 0 和 1 的二维网格地图，其中 1 表示陆地 0 表示水域。

网格中的格子水平和垂直方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

 

示例 :

输入:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

输出: 16

解释: 它的周长是下面图片中的 16 个黄色的边：

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/island-perimeter
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


///dfs
class Solution {///232ms 22.52% 95.2M 6.31%
    int rst, m, n;
    void dfs (vector<vector<int>>& grid, int i, int j, int di = -1)
    {
        static pair<int,int> dir[] {{1,0},{-1,0},{0,1},{0,-1}};
        grid[i][j] = 2;
        rst += 4;
        FOR(d,4) if (d != di)
        {
            auto [di,dj] = dir[d];
            if (i + di < 0 || m <= i + di || j + dj < 0 || n <= j + dj) continue;
            if (grid[i + di][j + dj] == 2) --rst;
            else if (grid[i + di][j + dj])
            {
                rst -= 2;
                dfs(grid,i+di,j+dj,d^1);
            }
        }
    }
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        m = grid.size();
        if (!m) return 0;
        n = grid[0].size();
        rst = 0;

        FOR(i,m)FOR(j,n) if (grid[i][j])
        {
            dfs (grid, i, j);
            return rst;
        }
        return rst;
    }
};

class SolutionV2 {///212ms 39.01% 94M 17.30%
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        pair<int,int> dir[]{{1,0},{0,1}};
        int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();

        int rst = 0;
        FOR(i,m)FOR(j,n) if (grid[i][j])
        {
            rst += 4;
            for (auto [di, dj] : dir)
                if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n && grid[i + di][j + dj])
                    rst -= 2;
        }
        return rst;
    }
};


class SolutionV1 {///256ms 9.99% 94.2% 9.22%
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        pair<int,int> dir[4]{{1,0},{-1,0},{0,1},{0,-1}};
        int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();

        int rst = 0;
        FOR(i,m)FOR(j,n) if (grid[i][j])
        {
            rst += 4;
            for (auto [di, dj] : dir)
                if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n && grid[i + di][j + dj])
                    --rst;
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{0,1,0,0},
         {1,1,1,0},
         {0,1,0,0},
         {1,1,0,0}}
    };
    for (auto x : xs)
        print(x), print(Solution().islandPerimeter(x)), print("===");
    return 0;
}
#endif
