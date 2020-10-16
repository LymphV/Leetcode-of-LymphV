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
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

 

示例 1：

输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
示例 2：

输入：
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
输出：[]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
///树+剪枝,unordered_map
class Solution ///236ms 57.14% 398.8M 5.00%
{
    unordered_map<int, unordered_map<char,int>> tree;
    unordered_map<int, int> leaves;

    int walk (string s, int i, int j)
    {
        int now = 0;
        ffor(k,i,j)
        {
            auto & node = tree[now];
            if (node.count(s[k]))
                now = node[s[k]];
            else return -1;
        }

        if (leaves.count(now)) return now;
        return -1;
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        if (!nw) return {};
        int lw = words[0].size();
        int n = lw * nw;
        if (m < n) return {};


        int cnt = 0;
        nw = words.size();


        FOR(i,nw)
        {
            int now = 0;
            FOR(j,words[i].size())
            {
                int & next = tree[now][words[i][j]];
                if (next) now = next;
                else now = next = ++cnt;
            }
            ++leaves[now];
        }


        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<int, int> cnt;
            int start = 1;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (start)
                {
                    cnt.clear();
                    start = 0;
                    FOR(j,nw)
                    {
                        int leaf = walk(s, l + j * lw, l + j * lw + lw);
                        if (~leaf) ++cnt[leaf];
                        else
                        {
                            start = 1;
                            l += j * lw;
                            r = l + n;
                            break;
                        }
                    }
                }
                else
                {
                    int leaf = walk(s, r - lw, r);
                    if (~leaf) ++cnt[leaf];
                    else
                    {
                        start = 1;
                        l = r - lw;
                        r = l + n;
                    }
                }
                if (start) continue;

                if (cnt == leaves) rst.emplace_back(l);

                int leaf = walk(s, l, l + lw);
                if (~leaf) --cnt[leaf];
            }
        }

        return rst;
    }
};


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///树+剪枝
class SolutionV8 {///212ms 58.44% 387.4M 5.00%
    using pic = pair<int,char>;

    map<pic, int> tree;
    unordered_map<int, int> leaves;

    int walk (string s, int i, int j)
    {
        int now = 0;
        ffor(k,i,j)
        {
            if (tree.count(pic(now,s[k])))
                now = tree[pic(now,s[k])];
            else return -1;
        }

        if (leaves.count(now)) return now;
        return -1;
    }


public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        if (!nw) return {};
        int lw = words[0].size();
        int n = lw * nw;
        if (m < n) return {};


        int cnt = 0;
        nw = words.size();


        FOR(i,nw)
        {
            int now = 0;
            FOR(j,words[i].size())
            {
                int & next = tree[pic(now,words[i][j])];
                if (next) now = next;
                else now = next = ++cnt;
            }
            ++leaves[now];
        }


        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<int, int> cnt;
            int start = 1;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (start)
                {
                    cnt.clear();
                    start = 0;
                    FOR(j,nw)
                    {
                        int leaf = walk(s, l + j * lw, l + j * lw + lw);
                        if (~leaf) ++cnt[leaf];
                        else
                        {
                            start = 1;
                            l += j * lw;
                            r = l + n;
                            break;
                        }
                    }
                }
                else
                {
                    int leaf = walk(s, r - lw, r);
                    if (~leaf) ++cnt[leaf];
                    else
                    {
                        start = 1;
                        l = r - lw;
                        r = l + n;
                    }
                }
                if (start) continue;

                if (cnt == leaves) rst.emplace_back(l);

                int leaf = walk(s, l, l + lw);
                if (~leaf) --cnt[leaf];
            }
        }

        return rst;
    }
};




///暴力2+再剪枝
class SolutionV7 {///24ms 99.96% 14.4M 75.04%
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        if (!nw) return {};
        int lw = words[0].size();
        int n = lw * nw;
        if (m < n) return {};

        unordered_map<string,int> mp;
        FOR(i,nw) ++mp[words[i]];
        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<string, int> cnt;
            int start = 1;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (start)
                {
                    cnt.clear();
                    start = 0;
                    FOR(j,nw)
                    {
                        auto now = begin(s) + l + j * lw;
                        string snow = string(now, now + lw);
                        if (mp.count(snow)) ++cnt[snow];
                        else
                        {
                            start = 1;
                            l += j * lw;
                            r = l + n;
                            break;
                        }
                    }
                }
                else
                {
                    auto now = begin(s) + r - lw;
                    string snow = string(now, now + lw);
                    if (mp.count(snow)) ++cnt[snow];
                    else
                    {
                        start = 1;
                        l = r - lw;
                        r = l + n;
                    }
                }
                if (start) continue;

                if (cnt == mp) rst.emplace_back(l);

                auto now = begin(s) + l;
                string snow = string(now, now + lw);
                if (mp.count(snow)) --cnt[snow];
            }
        }
        return rst;
    }
};

///暴力2+剪枝
class SolutionV6 {///68ms 78.40% 17.5M 64.23%

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        if (!nw) return {};
        int lw = words[0].size();
        int n = lw * nw;
        if (m < n) return {};

        unordered_map<string,int> mp;
        FOR(i,nw) ++mp[words[i]];
        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<string, int> cnt;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (l == i)
                {
                    FOR(j,nw)
                    {
                        auto now = begin(s) + l + j * lw;
                        string snow = string(now, now + lw);
                        if (mp.count(snow)) ++cnt[snow];
                    }
                }
                else
                {
                    auto now = begin(s) + r - lw;
                    string snow = string(now, now + lw);
                    if (mp.count(snow)) ++cnt[snow];
                }


                if (cnt == mp) rst.emplace_back(l);

                auto now = begin(s) + l;
                string snow = string(now, now + lw);
                if (mp.count(snow)) --cnt[snow];
            }
        }
        return rst;
    }
};


///暴力2 + hash
class SolutionV5 {///184ms 62.17% 33.8M 30.92%
    using ll = long long;
    ll hash (string s, ll p = 11)
    {
        ll M = (ll(1) << 50) - 1;
        return accumulate(begin(s), end(s), ll(0), [&p, &M](ll rst, char c){return ll((rst * p + c - 'a') & M);});
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        int n = accumulate(begin(words), end(words), 0, [](int a, string b){return a + b.size();});
        if (m < n) return {};

        int lw = words[0].size();

        ll ha1 = 0, ha2 = 0;
        unordered_map<string,int> mp;
        FOR(i,nw) ++mp[words[i]], ha2 ^= hash(words[i]);


        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<string, int> cnt;
            ha1 = 0;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (l == i)
                {
                    FOR(j,nw)
                    {
                        auto now = begin(s) + l + j * lw;
                        string snow = string(now, now + lw);
                        ++cnt[snow];
                        ha1 ^= hash(snow);
                    }
                }
                else
                {
                    auto now = begin(s) + r - lw;
                    string snow = string(now, now + lw);
                    ++cnt[snow];
                    ha1 ^= hash(snow);
                }


                if (ha1 == ha2 && cnt == mp) rst.emplace_back(l);

                auto now = begin(s) + l;
                string snow = string(now, now + lw);
                if (!--cnt[snow]) cnt.erase(snow);
                ha1 ^= hash(snow);
            }
        }
        return rst;
    }
};



///暴力2
class SolutionV4 {///120ms 67.43% 25.5M 36.98%
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = s.size();
        int nw = words.size();
        int n = accumulate(begin(words), end(words), 0, [](int a, string b){return a + b.size();});
        if (m < n) return vector<int>();

        int lw = words[0].size();

        unordered_map<string,int> mp;
        FOR(i,nw) ++mp[words[i]];
        vector<int> rst;
        FOR(i,lw)
        {
            unordered_map<string, int> cnt;
            for (int l = i, r = i + n; r <= m; l += lw, r += lw)
            {
                if (l == i)
                {
                    FOR(j,nw)
                    {
                        auto now = begin(s) + l + j * lw;
                        ++cnt[string(now, now + lw)];
                    }
                }
                else
                {
                    auto now = begin(s) + r - lw;
                    ++cnt[string(now, now + lw)];
                }


                if (cnt == mp) rst.emplace_back(l);

                auto now = begin(s) + l;
                string snow = string(now, now + lw);
                if (!--cnt[snow]) cnt.erase(snow);
            }
        }
        return rst;
    }
};


///暴力
class SolutionV3 {///TLE
    using pic = pair<int,char>;
    using ll = long long;

    int nw;
    map<pic, int> tree;
    int cnt;


    bool cmp (string s, int i, int j, unordered_map<int, int> leaves)
    {
        int now = 0;
        ffor(k,i,j)
        {
            if (tree.count(pic(now,s[k])))
            {
                now = tree[pic(now,s[k])];
                if (leaves.count(now) && leaves[now])
                {
                    --leaves[now];
                    now = 0;
                }
            }
            else return 0;
        }
        return !now;
    }

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        cnt = 0;
        int m = s.size();
        nw = words.size();
        int n = accumulate(begin(words), end(words), 0, [](int a, string b){return a + b.size();});
        if (m < n) return vector<int>();

        unordered_map<int, int> leaves;
        FOR(i,nw)
        {
            int now = 0;
            FOR(j,words[i].size())
            {
                int & next = tree[pic(now,words[i][j])];
                if (next) now = next;
                else now = next = ++cnt;
            }
            ++leaves[now];
        }

        vector<int> rst;
        for (int i = 0, j = n; j <= m; ++i, ++j)
        {
            if (cmp(s,i,j,leaves)) rst.emplace_back(i);
        }
        return rst;
    }
};


///降低碰撞
class SolutionV2 {///1052ms 18.44% 143.9M 8.94%
    using pic = pair<int,char>;
    using ll = long long;

    int nw;
    map<pic, int> tree;
    int cnt;

    ll f (char c)
    {
        int b = (c - 'a') % 32;
        if (b < 0) b += 32;
        return ll(1) << b;
    }

    bool cmp (string s, int i, int j, unordered_map<int, int> leaves)
    {
        int now = 0;
        ffor(k,i,j)
        {
            print(k,now,s[k]);
            if (tree.count(pic(now,s[k])))
            {
                now = tree[pic(now,s[k])];
                if (leaves.count(now) && leaves[now])
                {
                    --leaves[now];
                    now = 0;
                }
            }
            else return 0;
        }
        return !now;
    }

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        cnt = 0;
        int m = s.size();
        nw = words.size();
        int n = accumulate(begin(words), end(words), 0, [](int a, string b){return a + b.size();});
        if (m < n) return vector<int>();

        unordered_map<int, int> leaves;
        ll ha1 = 0, ha2 = 0;
        FOR(i,n-1) ha1 += f(s[i]);
        FOR(i,nw)
        {
            int now = 0;
            FOR(j,words[i].size())
            {
                ha2 += f(words[i][j]);
                int & next = tree[pic(now,words[i][j])];
                if (next) now = next;
                else now = next = ++cnt;
            }
            ++leaves[now];
        }

        vector<int> rst;
        for (int i = 0, j = n; j <= m; ++i, ++j)
        {
            ha1 += f(s[j-1]);
            print(ha1,ha2, i, j);
            if (ha1 == ha2 && cmp(s,i,j,leaves)) rst.emplace_back(i);

            ha1 -= f(s[i]);
        }
        return rst;
    }
};

class SolutionV1 {///908ms 24.40% 143.8M 8.94%
    using pic = pair<int,char>;

    int nw;
    map<pic, int> tree;
    int cnt;

    int f (char c)
    {
        int b = (c - 'a') % 32;
        if (b < 0) b += 32;
        return 1 << b;
    }

    bool cmp (string s, int i, int j, unordered_map<int, int> leaves)
    {print(string(begin(s) + i, begin(s) + j),i,j);
        int now = 0;
        ffor(k,i,j)
        {
            print(k,now,s[k]);
            if (tree.count(pic(now,s[k])))
            {
                now = tree[pic(now,s[k])];
                print("\t",now,leaves);
                if (leaves.count(now) && leaves[now])
                {
                    --leaves[now];
                    now = 0;
                }
            }
            else return 0;
        }
        return !now;
    }

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        cnt = 0;
        int m = s.size();
        nw = words.size();
        int n = accumulate(begin(words), end(words), 0, [](int a, string b){return a + b.size();});
        if (m < n) return vector<int>();

        unordered_map<int, int> leaves;
        int ha1 = 0, ha2 = 0;
        FOR(i,n-1) ha1 ^= f(s[i]);
        FOR(i,nw)
        {
            int now = 0;
            FOR(j,words[i].size())
            {
                ha2 ^= f(words[i][j]);
                int & next = tree[pic(now,words[i][j])];
                if (next) now = next;
                else now = next = ++cnt;
            }
            ++leaves[now];
        }
print(m,n);
print(tree);
print(leaves);

        vector<int> rst;
        for (int i = 0, j = n; j <= m; ++i, ++j)
        {
            ha1 ^= f(s[j-1]);
            print(ha1,ha2, i, j);
            if (ha1 == ha2 && cmp(s,i,j,leaves)) rst.emplace_back(i);

            ha1 ^= f(s[i]);
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<string,vector<string>>> xs{
        {"barfoothefoobarman",{"foo","bar"}},
        {"wordgoodgoodgoodbestword",{"word","good","best","word"}},
        {"abababab",{"ab","ba"}},
        {"lingmindraboofooowingdingbarrwingmonkeypoundcake",{"fooo","barr","wing","ding","wing"}},
        {"wordgoodgoodgoodbestword",{"word","good","best","good"}}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().findSubstring(x,y)), print("===");
    return 0;
}
#endif
