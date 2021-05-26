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
有台奇怪的打印机有以下两个特殊要求：

打印机每次只能打印由 同一个字符 组成的序列。
每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数。

 
示例 1：

输入：s = "aaabbb"
输出：2
解释：首先打印 "aaa" 然后打印 "bbb"。
示例 2：

输入：s = "aba"
输出：2
解释：首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 'a'。
 

提示：

1 <= s.length <= 100
s 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/strange-printer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///20ms 95.96% 6M 91.91%
    using vi = vector<int>;
    static const int N = 26;
public:
    string shorten (string s)
    {
        string rst;
        rst += s[0];
        for(char c : s) if (c != rst.back()) rst += c;
        return rst;
    }

    int strangePrinter(string s) {
        s = shorten(s);
        int rst = 0, n = s.size();
        int dp[n][n];
        FOR(i,n) dp[i][i] = 1;

        ffor(l,1,n)
        for (int i = 0, j = l; j < n; ++i, ++j)
        {
            int t = l + 1;
            if (s[i] == s[j]) t = dp[i][j - 1];
            else ffor(k,i,j) t = min(t, dp[i][k] + dp[k + 1][j]);
            dp[i][j] = t;
        }
        return dp[0][n - 1];
    }
};

class SolutionV2 {///40ms 73.40% 6M 97.87%
    using vi = vector<int>;
    static const int N = 26;
public:
    string shorten (string s)
    {
        string rst;
        rst += s[0];
        for(char c : s) if (c != rst.back()) rst += c;
        return rst;
    }

    int strangePrinter(string s) {
        s = shorten(s);
        int rst = 0, n = s.size();
        int dp[n][n];
        FOR(i,n) dp[i][i] = 1;

        ffor(l,1,n)
        for (int i = 0, j = l; j < n; ++i, ++j)
        {
            int t = l + 1;
            if (s[i] == s[j])
            {
                t = dp[i + 1][j - 1] + 1;
                ffor(k,i,j) t = min(t , dp[i][k] + dp[k + 1][j] - 1);
            }
            else ffor(k,i,j) t = min(t, dp[i][k] + dp[k + 1][j]);
            dp[i][j] = t;
        }
        return dp[0][n - 1];
    }
};


class SolutionV1 {///WA
    using vi = vector<int>;
    static const int N = 26;
public:
    string shorten (string s)
    {
        string rst;
        rst += s[0];
        for(char c : s) if (c != rst.back()) rst += c;
        return rst;
    }

    int strangePrinter(string s) {
        s = shorten(s);
        print (s);
        int rst = 0, n = s.size();
        string ss(n, '0');
        vi last[N];
        FOR(i,n) last[s[i] - 'a'].emplace_back(i);

        FOR(i,n) if (s[i] != ss[i])
        {
            ++rst;
            int stop;
            vi & v = last[s[i] - 'a'];
            for (stop = v.size() - 1; s[v[stop]] == ss[v[stop]]; --stop);

            for (int j = i; j <= v[stop]; ++j)
                ss[j] = s[i];
            print (ss, rst);
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<string> xs{"tbgtgb"
    , "abcabcabc"
    ,"baacdddaaddaaaaccbddbcabdaabdbbcdcbbbacbddcabcaaa"
    };

    for (auto & x : xs) print (Solution().shorten(x));

    for (auto & x : xs)
        print(x), print(Solution().strangePrinter(x)), print("===");
    return 0;
}
#endif
