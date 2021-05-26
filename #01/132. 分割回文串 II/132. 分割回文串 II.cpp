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
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。

返回符合要求的 最少分割次数 。

 

示例 1：

输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：

输入：s = "a"
输出：0
示例 3：

输入：s = "ab"
输出：1
 

提示：

1 <= s.length <= 2000
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///44ms 56.88% 19.2M 23.94%
    using vi = vector<int>;

    vector<vi> judge;
public:
    int minCut(string s) {
        int n = s.size();
        judge = vector<vi>(n, vi(n,1));
        for (int i = n - 1; ~i; --i) ffor(j,i+1,n)
            judge[i][j] = s[i] == s[j] && judge[i + 1][j - 1];
        vi rst(n, n);
        FOR(j,n)
        {
            if (judge[0][j]) rst[j] = 0;
            ffor(i,1,j+1) if (judge[i][j]) rst[j] = min(rst[j], rst[i - 1] + 1);
        }
        return rst[n - 1];
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<string> xs{"aab", "cdd"};
    for (auto & x : xs)
        print(x), print(Solution().minCut(x)), print("===");
    return 0;
}
#endif
