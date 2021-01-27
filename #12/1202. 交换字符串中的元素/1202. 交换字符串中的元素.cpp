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
给你一个字符串 s，以及该字符串中的一些「索引对」数组 pairs，其中 pairs[i] = [a, b] 表示字符串中的两个索引（编号从 0 开始）。

你可以 任意多次交换 在 pairs 中任意一对索引处的字符。

返回在经过若干次交换后，s 可以变成的按字典序最小的字符串。

 

示例 1:

输入：s = "dcab", pairs = [[0,3],[1,2]]
输出："bacd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[1] 和 s[2], s = "bacd"
示例 2：

输入：s = "dcab", pairs = [[0,3],[1,2],[0,2]]
输出："abcd"
解释：
交换 s[0] 和 s[3], s = "bcad"
交换 s[0] 和 s[2], s = "acbd"
交换 s[1] 和 s[2], s = "abcd"
示例 3：

输入：s = "cba", pairs = [[0,1],[1,2]]
输出："abc"
解释：
交换 s[0] 和 s[1], s = "bca"
交换 s[1] 和 s[2], s = "bac"
交换 s[0] 和 s[1], s = "abc"
 

提示：

1 <= s.length <= 10^5
0 <= pairs.length <= 10^5
0 <= pairs[i][0], pairs[i][1] < s.length
s 中只含有小写英文字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/smallest-string-with-swaps
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///324ms 68.40% 36.8M 97.17%
    using vi = vector<int>;
    class UFSet
    {
        vi father, level;
    public:
        UFSet (int n): father(n), level(n)
        {
            FOR(i,n) father[i] = i, level[i] = 0;
        }
        int find (int i)
        {
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        UFSet ufs(n);
        for(auto & x : pairs) ufs.unite(x[0], x[1]);
        unordered_map<int, string> rst;
        FOR(i,n) rst[ufs.find(i)] += s[i];
        for (auto & [k, v] : rst) sort(rbegin(v), rend(v));

        FOR(i,n)
        {
            string & t = rst[ufs.find(i)];
            s[i] = t.back();
            t.pop_back();
        }
        return s;
    }
};

class SolutionV3 {///TLE
    using vi = vector<int>;
    class UFSet
    {
        vi father, level;
    public:
        UFSet (int n): father(n), level(n)
        {
            FOR(i,n) father[i] = i, level[i] = 0;
        }
        int find (int i)
        {
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
        vector<vi> cluster ()
        {
            vector<vi> rst;

            int n = father.size();
            FOR(i,n) if (i == find(i)) rst.push_back({i});

            for (auto & v : rst) FOR(i,n)
                if (i != v[0] && find(i) == v[0])
                    v.push_back(i);
            return rst;
        }
    };
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        UFSet ufs(n);
        for(auto & x : pairs) ufs.unite(x[0], x[1]);

        auto && clusters = ufs.cluster();

        unordered_map<int, string> rst;
        for (vi & c : clusters)
        {
            string & t = rst[c[0]];
            for (int x : c) t += s[x];
        }
        for (auto & [k, v] : rst) sort(rbegin(v), rend(v));

        FOR(i,n)
        {
            string & t = rst[ufs.find(i)];
            s[i] = t.back();
            t.pop_back();
        }
        return s;
    }
};



class SolutionV2 {///428ms 30.00% 61.6M 8.49%
    using vi = vector<int>;
    void dfs (const string & s, string & t, vector<char> & b, const vector<vi> & graph, vi & ind, int now, int root)
    {
        ind.emplace_back(now), t += s[now];
        for (auto x : graph[now]) if (!b[x])
        {
            b[x] = 1, ind[x] = root;
            dfs(s, t, b, graph, ind, x, root);
        }
    }
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vi> graph(n, vi{});
        for(auto & x : pairs)
            graph[x[0]].emplace_back(x[1]), graph[x[1]].emplace_back(x[0]);

        vector<string> rst(n);
        vi ind(n, 0);
        vector<char> b(n, 0);
        FOR(i,n) if (!b[i])
        {
            string & t = rst[i];
            b[i] = 1, ind[i] = i;
            dfs(s, t, b, graph, ind, i, i);
            sort(rbegin(t), rend(t));
        }

        FOR(i,n)
        {
            s[i] = rst[ind[i]].back();
            rst[ind[i]].pop_back();
        }
        return s;
    }
};



class SolutionV1 {///468ms 22.80% 58.4M 11.33%
    using vi = vector<int>;
    void dfs (const string & s, string & t, vector<char> & b, const vector<vi> & graph, vi & ind, int now)
    {
        ind.emplace_back(now), t += s[now];
        for (auto x : graph[now]) if (!b[x])
        {
            b[x] = 1;
            dfs(s, t, b, graph, ind, x);
        }
    }
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vi> graph(n, vi{});
        for(auto & x : pairs)
            graph[x[0]].emplace_back(x[1]), graph[x[1]].emplace_back(x[0]);

        string rst = s;
        vector<char> b(n, 0);
        FOR(i,n) if (!b[i])
        {
            string t;
            vi ind;
            b[i] = 1;
            dfs(s, t, b, graph, ind, i);

            sort(begin(ind), end(ind));
            sort(begin(t), end(t));
            FOR(j,t.size()) rst[ind[j]] = t[j];
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string, vector<vi>>> xs{
        {"dcab", {{0,3}, {1,2}}},
        {"cba", {{0,1},{1,2}}}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().smallestStringWithSwaps(x, y)), print("===");
    return 0;
}
#endif
