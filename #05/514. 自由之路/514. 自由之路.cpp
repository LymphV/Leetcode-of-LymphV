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
电子游戏“辐射4”中，任务“通向自由”要求玩家到达名为“Freedom Trail Ring”的金属表盘，并使用表盘拼写特定关键词才能开门。

给定一个字符串 ring，表示刻在外环上的编码；给定另一个字符串 key，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。

最初，ring 的第一个字符与12:00方向对齐。您需要顺时针或逆时针旋转 ring 以使 key 的一个字符在 12:00 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符。

旋转 ring 拼出 key 字符 key[i] 的阶段中：

您可以将 ring 顺时针或逆时针旋转一个位置，计为1步。旋转的最终目的是将字符串 ring 的一个字符与 12:00 方向对齐，并且这个字符必须等于字符 key[i] 。
如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1 步。按完之后，您可以开始拼写 key 的下一个字符（下一阶段）, 直至完成所有拼写。
示例：

 


 
输入: ring = "godding", key = "gd"
输出: 4
解释:
 对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。
 对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"。
 当然, 我们还需要1步进行拼写。
 因此最终的输出是 4。
提示：

ring 和 key 的字符串长度取值范围均为 1 至 100；
两个字符串中都只有小写字符，并且均可能存在重复字符；
字符串 key 一定可以由字符串 ring 旋转拼出。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/freedom-trail
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///记录位置，最近的左右，不如暴力贪心
class Solution {///32ms 64.09% 14.3M 19.34%
    using vi = vector<int>;

    vector<vi> dp;
    string r, k;
    int m, n;
    unordered_map<char, vi> pos;

    int mod (int j)
    {
        j %= m;
        return j < 0 ? j + m : j;
    }
    int solve (int i = 0, int j = 0)
    {
        if (i == n) return 0;
        int & rst = dp[i][j];
        if (rst != -1) return rst;

        vi & ps = pos[k[i]];
        auto p = lower_bound(begin(ps), end(ps), j);
        if (p == end(ps))
        {
            int left = ps.back(), right = ps.front();
            rst = min(min({abs(left - j), left + m - j, j + m - left}) + solve(i + 1, left),
                      min({abs(right - j), right + m - j, j + m - right}) + solve(i + 1, right));
        }
        else if (*p == j) rst = solve(i + 1, j);
        else
        {
            int left = (p == begin(ps) ? ps.back() : *(p - 1)), right = *p;
            rst = min(min({abs(left - j), left + m - j, j + m - left}) + solve(i + 1, left),
                      min({abs(right - j), right + m - j, j + m - right}) + solve(i + 1, right));
        }
        return rst;
    }

public:
    int findRotateSteps(string ring, string key) {
        r = ring, k = key;
        m = ring.size(), n = key.size();
        dp = vector<vi> (n, vi(m, -1));
        FOR(i,m) pos[ring[i]].emplace_back(i);

        return n + solve();
    }
};

///记录位置
class SolutionV2 {///52ms 41.99% 14.3M 18.78%
    using vi = vector<int>;

    vector<vi> dp;
    string r, k;
    int m, n;
    unordered_map<char, vi> pos;

    int mod (int j)
    {
        j %= m;
        return j < 0 ? j + m : j;
    }
    int solve (int i = 0, int j = 0)
    {
        if (i == n) return 0;
        int & rst = dp[i][j];
        if (rst != -1) return rst;
        for (int next : pos[k[i]])
        {
            int value = min({abs(next - j), next + m - j, j + m - next}) + solve(i + 1, next);
            if (rst == -1) rst = value;
            rst = min(rst, value);
        }
        return rst;
    }

public:
    int findRotateSteps(string ring, string key) {
        r = ring, k = key;
        m = ring.size(), n = key.size();
        dp = vector<vi> (n, vi(m, -1));
        FOR(i,m) pos[ring[i]].emplace_back(i);

        return n + solve();
    }
};

///贪心左右最近，然后dp
class SolutionV1 {///20ms 88.40% 13.3M 27.62%
    using vi = vector<int>;

    vector<vi> dp;
    string r, k;
    int m, n;

    int mod (int j)
    {
        j %= m;
        return j < 0 ? j + m : j;
    }
    int solve (int i = 0, int j = 0)
    {
        if (i == n) return 0;
        int & rst = dp[i][j];
        if (rst != -1) return rst;
        int left = j, stepL = 0, right = j, stepR = 0;
        for (; r[left] != k[i]; left = mod(left - 1), ++stepL);
        for (; r[right] != k[i]; right = mod(right + 1), ++stepR);
        return rst = min(stepL + solve(i + 1, left), stepR + solve(i + 1, right));
    }

public:
    int findRotateSteps(string ring, string key) {
        r = ring, k = key;
        m = ring.size(), n = key.size();
        dp = vector<vi> (n, vi(m, -1));

        return n + solve();
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs
    {
        //{},
        {"godding", "gd"}
    };

    for (auto [x,y] : xs)
        print(x,y), print(Solution().findRotateSteps(x,y)), print("===");
    return 0;
}
#endif
