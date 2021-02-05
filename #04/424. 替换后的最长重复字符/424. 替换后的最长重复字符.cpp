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
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。

注意：字符串长度 和 k 不会超过 104。

 

示例 1：

输入：s = "ABAB", k = 2
输出：4
解释：用两个'A'替换为两个'B',反之亦然。
示例 2：

输入：s = "AABABBA", k = 1
输出：4
解释：
将中间的一个'A'替换为'B',字符串变为 "AABBBBA"。
子串 "BBBB" 有最长重复字母, 答案为 4。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-repeating-character-replacement
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 98.26% 6.9M 94.99%
    using vi = vector<int>;
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        if (!n) return 0;
        vi cnt(26, 0);
        int rst = 0, maxCnt = 0;
        for (int i = 0, j = 1; j <= n; ++j)
        {
            maxCnt = max(maxCnt, ++cnt[s[j - 1] - 'A']);
            if (k + maxCnt < j - i)
            {
                --cnt[s[i] - 'A'];
                ++i;
            }
            rst = max(rst, j - i);
        }
        return rst;
    }
};

class SolutionV2 {///16ms 43.17% 6.9M 90.22%
    using vi = vector<int>;
    using sc = unordered_set<char>;
    using vc = vector<unordered_set<char>>;
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        if (!n) return 0;
        vi cnt(26, 0);
        int rst = 0;
        for (int i = 0, j = 1; j <= n; ++j)
        {
            ++cnt[s[j - 1] - 'A'];
            if (k + *max_element(begin(cnt), end(cnt)) < j - i)
            {
                --cnt[s[i] - 'A'];
                ++i;
            }
            rst = max(rst, j - i);
        }
        return rst;
    }
};

class SolutionV1 {///WA
    using vi = vector<int>;
    using sc = unordered_set<char>;
    using vc = vector<unordered_set<char>>;
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        if (!n) return 0;
        ++k;
        vector<vi> dp(n, vi(k, 0));
        vector<vc> last(n, vc(k, sc{}));
        dp[0][0] = 1, last[0][0].insert(s[0]);
        ffor(i,1,n) dp[i][0] = s[i] == s[i - 1] ? dp[i - 1][0] + 1 : 1, last[i][0].insert(s[i]);
        FOR(i,n)ffor(j,1,k)
        {
            if (i < j) dp[i][j] = i + 1;
            else if (last[i - 1][j].empty() || last[i - 1][j].count(s[i]))
            {
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + 1;
                if (dp[i - 1][j] < dp[i - 1][j - 1]) last[i][j] = last[i - 1][j - 1];
                else if (dp[i - 1][j - 1] < dp[i - 1][j]) last[i][j].insert(s[i]);
                else
                {
                    last[i][j].insert(s[i]);
                    for (auto x : last[i - 1][j - 1]) last[i][j].insert(x);
                }
            }
            else dp[i][j] = dp[i - 1][j - 1] + 1, last[i][j] = last[i - 1][j - 1];
        }
        print(dp);
        print(last);
        int rst = 0;
        --k;
        FOR(i,n) rst = max(rst, dp[i][k]);
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<string,int>> xs{
         {"ABAB", 2},
         {"AABABBA",1},
         {"KJRGKSKKOK",5},
         {"KJRGK",3},
         {"BDPDPFP", 2}
         //{"EQQEJDOBDPDPFPEIAQLQGDNIRDDGEHJIORMJPKGPLCPDFMIGHJNIIRSDSBRNJNROBALNSHCRFBASTLRMENCCIBJLGAITBFCSMPRO",2}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().characterReplacement(x,y)), print("===");
    return 0;
}
#endif
