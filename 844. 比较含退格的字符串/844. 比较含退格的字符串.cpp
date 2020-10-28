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
给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，判断二者是否相等，并返回结果。 # 代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

 

示例 1：

输入：S = "ab#c", T = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。
示例 2：

输入：S = "ab##", T = "c#d#"
输出：true
解释：S 和 T 都会变成 “”。
示例 3：

输入：S = "a##c", T = "#a#c"
输出：true
解释：S 和 T 都会变成 “c”。
示例 4：

输入：S = "a#c", T = "b"
输出：false
解释：S 会变成 “c”，但 T 仍然是 “b”。
 

提示：

1 <= S.length <= 200
1 <= T.length <= 200
S 和 T 只含有小写字母以及字符 '#'。
 

进阶：

你可以用 O(N) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/backspace-string-compare
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 51.03% 6.3M 60.91%
public:
    bool backspaceCompare(string S, string T) {
        int m = S.size() - 1, n = T.size() - 1;
        int i = 0, j = 0;
        while (0 <= m || 0 <= n)
        {print(m,n, S[m], T[n]);
            if (0 <= m && S[m] == '#')
            {
                --m, ++i;
                continue;
            }
            else if (i)
            {
                --m, --i;
                continue;
            }
            if (0 <= n && T[n] == '#')
            {
                --n, ++j;
                continue;
            }
            else if (j)
            {
                --n, --j;
                continue;
            }
            if (0 <= m && 0 <= n && S[m] == T[n])
            {
                --m, --n;
                continue;
            }
            return 0;
        }
        return 1;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        {"a#c", "b"},
        {"a##c", "#a#c"},
        {"ab##", "c#d#"},
        {"ab#c","ad#c"}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().backspaceCompare(x,y)), print("===");
    return 0;
}
#endif
