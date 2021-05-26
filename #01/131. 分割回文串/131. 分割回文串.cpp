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
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

回文串 是正着读和反着读都一样的字符串。

 

示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]
 

提示：

1 <= s.length <= 16
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///148ms 72.72% 77.9M 32.98%
    using vs = vector<string>;
    using vi = vector<char>;

    vector<vi> judge;
    vector<vs> rst;
    vs now;

    void solve (string s, int i = 0)
    {
        if (i == s.size()) rst.emplace_back(now);
        for (int j = i; j < s.size(); ++j) if (judge[i][j])
        {
            now.emplace_back(string(s.begin() + i, s.begin() + j + 1));
            solve(s, j + 1);
            now.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        judge = vector<vi>(n, vi(n,1));
        for (int i = n - 1; ~i; --i) ffor(j,i+1,n)
            judge[i][j] = s[i] == s[j] && judge[i + 1][j - 1];
        solve(s);
        return rst;
    }
};

class SolutionV4 {///164ms 61.71% 78.1M 29.62%
    using vs = vector<string>;
    using vi = vector<char>;

    vector<vi> judge;
    vector<vs> rst;

    void solve (string s, vs & now, int i = 0)
    {
        if (i == s.size()) rst.emplace_back(now);
        for (int j = i; j < s.size(); ++j) if (judge[i][j])
        {
            now.emplace_back(string(s.begin() + i, s.begin() + j + 1));
            solve(s, now, j + 1);
            now.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        judge = vector<vi>(n, vi(n,1));
        for (int i = n - 1; ~i; --i) ffor(j,i+1,n)
            judge[i][j] = s[i] == s[j] && judge[i + 1][j - 1];
        vs now;
        solve(s, now);
        return rst;
    }
};

class SolutionV3 {///164ms 61.71% 78.3M 26.08%
    using vs = vector<string>;
    using vi = vector<int>;

    unordered_map<int, vi> judge;
    vector<vs> rst;

    void solve (string s, vs & now, int i = 0)
    {
        if (i == s.size()) rst.emplace_back(now);
        for (int j : judge[i])
        {
            now.emplace_back(string(s.begin() + i, s.begin() + j + 1));
            solve(s, now, j + 1);
            now.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        FOR(i,n) judge[i].emplace_back(i);
        FOR(i,n)for(int j = 1; 0 <= i - j && i + j < n; ++j)
        {
            if (s[i - j] == s[i + j]) judge[i - j].emplace_back(i + j);
            else break;
        }
        FOR(i,n-1)for (int j = 0; 0 <= i - j && i + 1 + j < n; ++j)
        {
            if (s[i - j] == s[i + 1 + j]) judge[i - j].emplace_back(i + 1 + j);
            else break;
        }
        vs now;
        solve(s, now);
        return rst;
    }
};

class SolutionV2 {///156ms 66.32% 78M 32.28%
    using vs = vector<string>;
    using vi = vector<char>;

    vector<vi> judge;
    vector<vs> rst;

    void solve (string s, vs & now, int i = 0)
    {
        if (i == s.size()) rst.emplace_back(now);
        for (int j = i; j < s.size(); ++j) if (judge[i][j])
        {
            now.emplace_back(string(s.begin() + i, s.begin() + j + 1));
            solve(s, now, j + 1);
            now.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        judge = vector<vi>(n, vi(n,0));
        FOR(i,n) judge[i][i] = 1;
        FOR(i,n)for(int j = 1; 0 <= i - j && i + j < n; ++j)
        {
            if (s[i - j] == s[i + j]) judge[i - j][i + j] = 1;
            else break;
        }
        FOR(i,n-1)for (int j = 0; 0 <= i - j && i + 1 + j < n; ++j)
        {
            if (s[i - j] == s[i + 1 + j]) judge[i - j][i + 1 + j] = 1;
            else break;
        }
        vs now;
        solve(s, now);
        return rst;
    }
};

class SolutionV1 {///200ms 45.86% 78.1M 27.94%
    using vs = vector<string>;
    using pii = pair<int,int>;

    set<pii> judge;
    vector<vs> rst;

    void solve (string s, vs & now, int i = 0)
    {
        if (i == s.size()) rst.emplace_back(now);
        for (int j = i; j < s.size(); ++j) if (i == j || judge.count(pii(i,j)))
        {
            now.emplace_back(string(s.begin() + i, s.begin() + j + 1));
            solve(s, now, j + 1);
            now.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        FOR(i,n)for(int j = 1; 0 <= i - j && i + j < n; ++j)
        {
            if (s[i - j] == s[i + j]) judge.insert(pii(i - j, i + j));
            else break;
        }
        FOR(i,n-1)for (int j = 0; 0 <= i - j && i + 1 + j < n; ++j)
        {
            if (s[i - j] == s[i + 1 + j]) judge.insert(pii(i - j, i + 1 + j));
            else break;
        }
        vs now;
        solve(s, now);
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<string> xs{"aab"};
    for (auto & x : xs)
        print(x), print(Solution().partition(x)), print("===");
    return 0;
}
#endif
