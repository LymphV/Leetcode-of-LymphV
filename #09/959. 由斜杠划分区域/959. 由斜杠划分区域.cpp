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
在由 1 x 1 方格组成的 N x N 网格 grid 中，每个 1 x 1 方块由 /、\ 或空格构成。这些字符会将方块划分为一些共边的区域。

（请注意，反斜杠字符是转义的，因此 \ 用 "\\" 表示。）。

返回区域的数目。

 

示例 1：

输入：
[
  " /",
  "/ "
]
输出：2
解释：2x2 网格如下：

示例 2：

输入：
[
  " /",
  "  "
]
输出：1
解释：2x2 网格如下：

示例 3：

输入：
[
  "\\/",
  "/\\"
]
输出：4
解释：（回想一下，因为 \ 字符是转义的，所以 "\\/" 表示 \/，而 "/\\" 表示 /\。）
2x2 网格如下：

示例 4：

输入：
[
  "/\\",
  "\\/"
]
输出：5
解释：（回想一下，因为 \ 字符是转义的，所以 "/\\" 表示 /\，而 "\\/" 表示 \/。）
2x2 网格如下：

示例 5：

输入：
[
  "//",
  "/ "
]
输出：3
解释：2x2 网格如下：

 

提示：

1 <= grid.length == grid[0].length <= 30
grid[i][j] 是 '/'、'\'、或 ' '。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regions-cut-by-slashes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 99.54% 9.8M
    using vi = vector<int>;
    int n;
    int getId (int x, int y, int z)
    {
        int i = z & 1, j = z >> 1;
        if (i) return n * (n + 1) + n * (x + j) + y;
        return n * (y + j) + x;
    }
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
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size(), m = 2 * n * (n + 1);
        this->n = n;
        UFSet ufs(m);
        FOR(i,n)FOR(j,n)
        {
            char & c = grid[i][j];
            int id0 = getId(i,j,0), id1 = getId(i,j,1), id2 = getId(i,j,2), id3 = getId(i,j,3);
            if (c == ' ')
                ufs.unite(id0,id1), ufs.unite(id1,id2), ufs.unite(id2,id3);
            else if (c == '/')
                ufs.unite(id0,id1), ufs.unite(id2,id3);
            else ufs.unite(id1,id2), ufs.unite(id0,id3);
        }
        int rst = 0;
        FOR(i,m) if (ufs.find(i) == i) ++rst;
        return rst;
    }
};

class SolutionV1 {///12ms 77.63% 10.4M 37.79%
    using vi = vector<int>;
    int n;
    int getId (int x, int y, int z)
    {
        return 4 * (n * x + y) + z;
    }
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
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        this->n = n;
        UFSet ufs(4 * n * n);
        FOR(i,n)ffor(j,1,n) ufs.unite(getId(i,j-1,2), getId(i,j,1)), ufs.unite(getId(j-1,i,3), getId(j,i,0));
        FOR(i,n)FOR(j,n)
        {
            char & c = grid[i][j];
            int id0 = getId(i,j,0), id1 = getId(i,j,1), id2 = getId(i,j,2), id3 = getId(i,j,3);
            if (c == ' ')
                ufs.unite(id0,id1), ufs.unite(id1,id3), ufs.unite(id2,id3);
            else if (c == '/')
                ufs.unite(id0,id1), ufs.unite(id2,id3);
            else ufs.unite(id1,id3), ufs.unite(id0,id2);
        }
        int rst = 0;
        FOR(i,4*n*n) if (ufs.find(i) == i) ++rst;
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vector<string>> xs{
        {
          " /",
          "/ "
        }
    };
    for (auto & x : xs)
        print(x), print(Solution().regionsBySlashes(x)), print("===");
    return 0;
}
#endif
