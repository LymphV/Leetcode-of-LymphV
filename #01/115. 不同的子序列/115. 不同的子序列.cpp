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
给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

示例 1：

输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)
rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
示例 2：

输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。
(上箭头符号 ^ 表示选取的字母)
babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
 

提示：

0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/distinct-subsequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///0ms 100.00% 6.6M 80.55%
    using ll = long long;
public:
    int numDistinct(string s, string t) {
        int m = t.size() + 1, n = s.size() + 1;
        ll dp[m][n];
        ffor(i,1,n) dp[0][i] = 0;
        dp[0][0] = 1;
        ffor(i,1,m)
        {
            dp[i][0] = 0;
            ll tot = dp[i - 1][0];
            char c = t[i - 1];
            ffor(j,1,n)
            {
                dp[i][j] = s[j - 1] == c ? tot : 0;
                tot += dp[i - 1][j];
            }
        }
        return int(accumulate(dp[m - 1], dp[m], 0));
    }
};

class SolutionV1 {///0ms 100.00% 6.4M 91.96%
    using ll = long long;
public:
    int numDistinct(string s, string t) {
        int m = t.size() + 1, n = s.size() + 1;
        ll dp[m][n];
        MS(dp, 0);
        dp[0][0] = 1;
        ffor(i,1,m)
        {
            dp[i][0] = 0;
            ll tot = dp[i - 1][0];
            char c = t[i - 1];
            ffor(j,1,n)
            {
                dp[i][j] = s[j - 1] == c ? tot : 0;
                tot += dp[i - 1][j];
            }
        }
        return int(accumulate(dp[m - 1], dp[m], 0));
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        {"xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo","rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys"}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().numDistinct(x,y)), print("===");
    return 0;
}
#endif
