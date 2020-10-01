#include <LymphV>

/**
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regular-expression-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


#define ffor(x,y,z) for (int x = y; x < z; ++x)

using si = set<int>;
class Regex
{
public:

    using psi = pair<string,int>;
    static map<psi,si> mp;
    static int node;
    static int getNode ()
    {
        return ++node;
    }
public:
    int start, stop;
    string r;

    Regex ()
    {
        r = "";
        start = getNode();
        stop = getNode();
        mp[psi("",start)].insert(stop);
    }
    Regex (char c)
    {
        r = string(1,c);
        start = getNode();
        stop = getNode();
        mp[psi(r,start)].insert(stop);
    }


    Regex & operator += (const Regex & r)
    {
        this->r += r.r;
        mp[psi("",stop)].insert(r.start);
        stop = r.stop;
        return *this;
    }

    Regex & addStar ()
    {
        if (start != stop)
        {
            r += "*";
            mp[psi("",stop)].insert(start);
            stop = start;
        }
        return *this;
    }

    static Regex compile (string s)
    {
        if (!s.size()) return Regex();
        stack<Regex> st;
        for (char c : s)
        {
            if (c == '*')
            {
                Regex r1 = st.top();st.pop();
                r1.addStar();
                if (st.empty()) st.push(r1);
                else
                {
                    Regex r2 = st.top();st.pop();
                    if (r1.r == ".*" && r2.r.size() > 1) st.push(r1);
                    else if (r2.r == ".*") st.push(r2);
                    else if (r1.r == r2.r) st.push(r1);
                    else {st.push(r2);st.push(r1);}
                }
            }
            else st.push(Regex(c));
        }
        while (st.size() > 1)
        {
            Regex r2 = st.top();st.pop();
            Regex r1 = st.top();st.pop();
            st.push(r1 += r2);
        }
        return st.top();
    }

    static si next (string s, int now)
    {
        auto next = mp.find(psi(s,now));
        if (next == mp.end()) return si();
        return next->second;
    }
};
map<pair<string,int>,si> Regex::mp;
int Regex::node = -1;


class Solution {
public:
    int stop;
    string s;


    bool dfs (int i, int now)
    {
        if (i == s.size())
        {
            if (now == stop) return 1;

            for (int next : Regex::next("",now))
                if (dfs(i,next)) return 1;
            return 0;
        }
        for (int next : Regex::next("",now))
            if (dfs(i,next)) return 1;

        for (int next : Regex::next(string(1,s[i]),now))
            if (dfs(i+1,next)) return 1;

        for (int next : Regex::next(".",now))
            if (dfs(i+1,next)) return 1;

        return 0;
    }

    bool isMatch(string str, string p) {
        auto r = Regex::compile(p);

        print(r.r);
        stop = r.stop, s = str;
        return dfs(0, r.start);
    }
};


class SolutionDp
{
public:
    bool isMatch(string s, string p)
    {
        vector<string> && pp = deal(p);
        s = '\0' + s;

        int m = s.size(), n = pp.size();
        bool dp[m][n];;
        dp[0][0] = 1;
        ffor(i,1,m) dp[i][0] = 0;
        ffor(j,1,n) dp[0][j] = pp[j].size() > 1 && dp[0][j-1];


        ffor(i,1,m)ffor(j,1,n)
            dp[i][j] = (dp[i-1][j-1] && isMatch(s[i],pp[j]))
                || (dp[i][j-1] && pp[j].size() > 1)
                || (dp[i-1][j] && pp[j].size() > 1 && (pp[j][0] == '.' || pp[j][0] == s[i]));

        return dp[m-1][n-1];
    }

    bool isMatch (char c, const string & r)
    {
        return r[0] == '.' || r[0] == c;
    }
    vector<string> deal (string p)
    {
        vector<string> rst{""};
        for (char c : p)
        {
            if (c == '*') rst.back() += c;
            else rst.push_back(string(1,c));
        }
        return rst;
    }
};


class SolutionStd {
public:
    bool isMatch(string s, string p) {
        return regex_match(s,regex(p));
    }
};










int main ()
{
    vector<pair<string,string>> xs{
        {"aa","a"},
        {"aa","a*"},
        {"ab",".*"},
        {"aab","c*a*b"},
        {"misissippi","mis*is*p*."},
        {"aaaaaaaaaaaaab","a*a*a*a*a*a*a*a*a*a*c"},
        {"aab","b.*"}
    };

    for (auto [x,r] : xs)
        print(x,r,Solution().isMatch(x,r));
    return 0;
}
