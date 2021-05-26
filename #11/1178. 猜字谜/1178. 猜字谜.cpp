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
外国友人仿照中国字谜设计了一个英文版猜字谜小游戏，请你来猜猜看吧。

字谜的迷面 puzzle 按字符串形式给出，如果一个单词 word 符合下面两个条件，那么它就可以算作谜底：

单词 word 中包含谜面 puzzle 的第一个字母。
单词 word 中的每一个字母都可以在谜面 puzzle 中找到。
例如，如果字谜的谜面是 "abcdefg"，那么可以作为谜底的单词有 "faced", "cabbage", 和 "baggage"；而 "beefed"（不含字母 "a"）以及 "based"（其中的 "s" 没有出现在谜面中）。
返回一个答案数组 answer，数组中的每个元素 answer[i] 是在给出的单词列表 words 中可以作为字谜迷面 puzzles[i] 所对应的谜底的单词数目。

 

示例：

输入：
words = ["aaaa","asas","able","ability","actt","actor","access"],
puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
输出：[1,1,3,2,4,0]
解释：
1 个单词可以作为 "aboveyz" 的谜底 : "aaaa"
1 个单词可以作为 "abrodyz" 的谜底 : "aaaa"
3 个单词可以作为 "abslute" 的谜底 : "aaaa", "asas", "able"
2 个单词可以作为 "absoryz" 的谜底 : "aaaa", "asas"
4 个单词可以作为 "actresz" 的谜底 : "aaaa", "asas", "actt", "access"
没有单词可以作为 "gaswxyz" 的谜底，因为列表中的单词都不含字母 'g'。
 

提示：

1 <= words.length <= 10^5
4 <= words[i].length <= 50
1 <= puzzles.length <= 10^4
puzzles[i].length == 7
words[i][j], puzzles[i][j] 都是小写英文字母。
每个 puzzles[i] 所包含的字符都不重复。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-valid-words-for-each-puzzle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///232ms 73.85% 44.8M 12.31%
    using vi = vector<int>;
    static const int N = 26;
    using bs = bitset<N>;

    bs toBs (const string & s) const
    {
        bs rst;
        for (char c : s) rst.set(c - 'a');
        return rst;
    }

    int solve (unordered_map<bs, int> & cnt, string & s)
    {
        bs all;
        ffor(i,1,s.size()) all.set(s[i] - 'a');
        int rst = 0;
        bs now = all;
        do
        {
            rst += cnt[now.set(s[0] - 'a')];
            now = bs(now.reset(s[0] - 'a').to_ullong() - 1) & all;
        }while (now != all);
        return rst;
    }

public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int m = words.size(), n = puzzles.size();
        unordered_map<bs, int> cnt;

        FOR(i,m) ++cnt[toBs(words[i])];
        vi rst(n, 0);
        FOR(i,n) rst[i] = solve(cnt, puzzles[i]);
        return rst;
    }
};

class SolutionV2 {///296ms 60.00% 45.2M 12.31%
    using vi = vector<int>;
    static const int N = 26;
    using bs = bitset<N>;

    bs toBs (const string & s) const
    {
        bs rst;
        for (char c : s) rst.set(c - 'a');
        return rst;
    }

    int dfs (unordered_map<bs, int> & cnt, bs & b, string & s, int now = 1)
    {
        if (now == s.size()) return cnt[b];
        int rst = dfs(cnt, b.set(s[now] - 'a'), s, now + 1);
        rst += dfs(cnt, b.reset(s[now] - 'a'), s, now + 1);
        return rst;
    }

public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int m = words.size(), n = puzzles.size();
        unordered_map<bs, int> cnt;

        FOR(i,m) ++cnt[toBs(words[i])];
        vi rst(n, 0);
        FOR(i,n)
        {
            bs b;
            b.set(puzzles[i][0] - 'a');
            rst[i] = dfs(cnt, b, puzzles[i]);
        }
        return rst;
    }
};


///python.set.__ior__
template <typename T>
unordered_set<T> & operator |= (unordered_set<T> & self, const unordered_set<T> & value)
{
    for (typename unordered_set<T>::const_iterator it = value.begin(); it != value.end(); ++it)
        self.insert(*it);
    return self;
}

///python.set.__and__
template <typename T>
int operator & (const unordered_set<T> & self, const unordered_set<T> & value)
{
    int rst = 0;
    for (typename unordered_set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
        if (value.find(*it) != value.end())
            ++rst;
    return rst;
}

class SolutionV1 {///TLE
    using vi = vector<int>;
    using si = unordered_set<int>;
    static const int N = 26;
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int m = words.size(), n = puzzles.size();
        vector<si> contain (N, si());
        FOR(i,m)for (char c : words[i]) contain[c - 'a'].insert(i);
        vi rst(n, 0);
        FOR(i,n)
        {
            if (contain[puzzles[i][0] - 'a'].empty())
            {
                rst[i] = 0;
                continue;
            }
            vi cnt(N, 0);
            for (char c : puzzles[i]) ++cnt[c - 'a'];
            si v;
            FOR(j,N) if (!cnt[j]) v |= contain[j];
            rst[i] = contain[puzzles[i][0] - 'a'].size() - (contain[puzzles[i][0] - 'a'] & v);
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    bitset<5> b = 5;
    print (b);
    auto a = b;
    a = bitset<5>(a.to_ulong() - 1) & b;
    print (a);
    a = bitset<5>(a.to_ulong() - 1) & b;
    print (a);

    vector<pair<vector<string>,vector<string>>> xs{
        {
            {"aaaa","asas","able","ability","actt","actor","access"},
            {"aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"}
        }
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().findNumOfValidWords(x, y)), print("===");
    return 0;
}
#endif
