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
给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
两个字符串完全匹配才算匹配成功。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。
示例 3:

输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。
示例 4:

输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".
示例 5:

输入:
s = "acdcb"
p = "a*c?b"
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/wildcard-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 94.94% 6.4M 96.70%
    using sit = string::iterator;
    int find (string & s, int m,  sit i, sit j, int now)
    {
        for (; now < m; ++now)
        {
            sit it = i;
            for (int t = 0; now + t < m; ++t, ++it)
            {
                if (*it != '?' && *it != s[now + t]) break;
            }
            if (it == j) return now;
        }
        return -1;
    }
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        for (; n && m && p[n - 1] != '*'; --n, --m)
            if (p[n - 1] != '?' && p[n - 1] != s[m - 1]) return 0;

        auto a = begin(s), b = begin(p);

        int i = 0, now = 0;

        for (; i < n && now < m && p[i] != '*'; ++i, ++now)
            if (p[i] != '?' && p[i] != s[now]) return 0;

        if (!(n - i))
        {
            if (!(m - now)) return 1;
            return 0;
        }

        for (int j; i < n; i = j)
        {
            for (; i < n && p[i] == '*'; ++i);
            if (i == n) break;
            for (j = i; j < n && p[j] != '*'; ++j);
            now = find(s, m, b + i, b + j, now);
            if (now == -1) return 0;
            now += (j - i);
        }
        return 1;
    }
};

class SolutionV6 {///16ms 90.81% 11M 66.90%
public:
    bool isMatch(string s, string p) {
        string pp;
        if (!p.empty())
        {
            pp += p[0];
            ffor(i,1,p.size())
            {
                if (p[i] == '*' && pp.back() == '*') continue;
                pp += p[i];
            }
        }
        int m = s.size() + 1, n = pp.size() + 1;
        int dp[m][n];
        dp[0][0] = 1;
        ffor(i,1,m)dp[i][0] = 0;
        ffor(j,1,n)
        {
            char c = pp[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m)
            {
                if (c == s[i - 1] || c == '?') dp[i][j] = dp[i - 1][j - 1];
                else if (c == '*') dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                else dp[i][j] = 0;
            }
        }
        return dp[m - 1][n - 1];
    }
};

class SolutionV5 {///24ms 89.83% 10.7M 78.37%
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        int dp[m][n];
        dp[0][0] = 1;
        ffor(i,1,m)dp[i][0] = 0;
        ffor(j,1,n)
        {
            char c = p[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m)
            {
                if (c == s[i - 1] || c == '?') dp[i][j] = dp[i - 1][j - 1];
                else if (c == '*') dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                else dp[i][j] = 0;
            }
        }
        return dp[m - 1][n - 1];
    }
};


class SolutionV4 {///28ms 89.09% 10.7M 78.32%
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        int dp[m][n];
        dp[0][0] = 1;
        ffor(i,1,m)dp[i][0] = 0;
        ffor(j,1,n)
        {
            char c = p[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m) switch (c)
            {
            case '*': dp[i][j] = dp[i][j - 1] || dp[i - 1][j];break;
            case '?': dp[i][j] = dp[i - 1][j - 1];break;
            default: dp[i][j] = dp[i - 1][j - 1] && c == s[i - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

class SolutionV3 {///20ms 90.48% 10.9M 75.53%
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        int dp[m][n];
        dp[0][0] = 1;
        ffor(i,1,m)dp[i][0] = 0;
        ffor(j,1,n)
        {
            char c = p[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m) switch (c)
            {
            case '*': dp[i][j] = dp[i - 1][j - 1] || dp[i][j - 1] || dp[i - 1][j];break;
            case '?': dp[i][j] = dp[i - 1][j - 1];break;
            default: dp[i][j] = dp[i - 1][j - 1] && c == s[i - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

class SolutionV2 {///84ms 64.39% 27.3M 16.85%
    using vi = vector<int>;
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        vector<vi> dp(m, vi(n, 0));
        dp[0][0] = 1;
        ffor(j,1,n)
        {
            char c = p[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m) switch (c)
            {
            case '*': dp[i][j] = dp[i - 1][j - 1] || dp[i][j - 1] || dp[i - 1][j];break;
            case '?': dp[i][j] = dp[i - 1][j - 1];break;
            default: dp[i][j] = dp[i - 1][j - 1] && c == s[i - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

class SolutionV1 {///84ms 64.39% 27.2M 21.6%
    using vi = vector<int>;
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        vector<vi> dp(m, vi(n, 0));
        dp[0][0] = 1;
        ffor(j,1,n)
        {
            char c = p[j - 1];
            dp[0][j] = dp[0][j - 1] && c == '*';
            ffor(i,1,m)
            {
                if (c == '*') dp[i][j] = dp[i - 1][j - 1] || dp[i][j - 1] || dp[i - 1][j];
                else if (c == '?') dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = dp[i - 1][j - 1] && c == s[i - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        /*{"adceb","*a*b"},
        {"", "**"},
        {
            "aa", "a"
        },*/
        {"mississippi","m??*ss*?i*pi"}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().isMatch(x,y)), print("===");
    return 0;
}
#endif
