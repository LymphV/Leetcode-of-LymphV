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
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

 

示例 1：


输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
示例 2：


输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true
示例 3：


输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
输出：false
 

提示：

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board 和 word 仅由大小写英文字母组成
 

进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-search
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///156ms 65.52% 7.1M 84.61%
    const int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int m, n;
    bool dfs (vector<vector<char>> & board, string & word, int i, int j, int k = 0)
    {
        if (k == word.size()) return 1;
        if (i < 0 || m <= i || j < 0 || n <= j || board[i][j] != word[k]) return 0;
        char c = board[i][j];
        board[i][j] = 0;
        FOR(d,4) if (dfs(board, word, i + dir[d][0], j + dir[d][1], k + 1)) return 1;
        board[i][j] = c;
        return 0;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        FOR(i,m)FOR(j,n)if (board[i][j] == word[0])
            if (dfs(board, word, i, j)) return 1;
        return 0;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
