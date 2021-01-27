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
给你一个 n 个点的带权无向连通图，节点编号为 0 到 n-1 ，同时还有一个数组 edges ，其中 edges[i] = [fromi, toi, weighti] 表示在 fromi 和 toi 节点之间有一条带权无向边。最小生成树 (MST) 是给定图中边的一个子集，它连接了所有节点且没有环，而且这些边的权值和最小。

请你找到给定图中最小生成树的所有关键边和伪关键边。如果从图中删去某条边，会导致最小生成树的权值和增加，那么我们就说它是一条关键边。伪关键边则是可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边。

请注意，你可以分别以任意顺序返回关键边的下标和伪关键边的下标。

 

示例 1：



输入：n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
输出：[[0,1],[2,3,4,5]]
解释：上图描述了给定图。
下图是所有的最小生成树。

注意到第 0 条边和第 1 条边出现在了所有最小生成树中，所以它们是关键边，我们将这两个下标作为输出的第一个列表。
边 2，3，4 和 5 是所有 MST 的剩余边，所以它们是伪关键边。我们将它们作为输出的第二个列表。
示例 2 ：



输入：n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
输出：[[],[0,1,2,3]]
解释：可以观察到 4 条边都有相同的权值，任选它们中的 3 条可以形成一棵 MST 。所以 4 条边都是伪关键边。
 

提示：

2 <= n <= 100
1 <= edges.length <= min(200, n * (n - 1) / 2)
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti <= 1000
所有 (fromi, toi) 数对都是互不相同的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class SolutionV4 {///WA
    using vi = vector<int>;
    using pii = pair<int,int>;
    using si = unordered_set<int>;
    using psi = pair<si,int>;

    class UFSet
    {
    public:
        vi father, level;
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
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

    int hpii (int a, int b)
    {
        return a * 10000 + b;
    }
    unordered_map<int, pair<pii,vi>> group (vi & es, vector<vi> & edges, UFSet & ufs)
    {
        unordered_map<int, pair<pii,vi>> rst;
        for (int i : es)
        {
            vi & e = edges[i];
            int a = ufs.find(e[0]), b = ufs.find(e[1]);
            if (b < a) swap(a, b);
            auto & [x, y] = rst[hpii(a,b)];
            if (y.empty()) x = pii(a,b);
            y.emplace_back(i);
        }
        return rst;
    }

    vi ke, nke;
    void kruskal (int n, vector<vi> & edges)
    {
        UFSet ufs(n);
        int m = edges.size();
        vi rst(m, 0);
        int tot = 0, cnt = 1;
        FOR(i,m)
        {
            int w = edges[i][2];
            vi es;
            ffor(j,i,m)
            {
                vi & e = edges[j];
                if (e[2] != w) break;
                i = j;
                if (!ufs.same(e[0], e[1])) es.emplace_back(j);
            }

            auto && groups = group(es, edges, ufs);
            for (auto & [k, v] : groups)
            {
                auto & [x, y] = v;

                if (1 < y.size()) for (int j : y)
                    nke.emplace_back(edges[j].back());
                else ke.emplace_back(edges[y[0]].back());
                ufs.unite(x.first, x.second);
                ++cnt;
            }
            if (cnt == n) break;
        }
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        FOR(i,m) edges[i].emplace_back(i);
        sort(begin(edges), end(edges), [](vi & a, vi & b){return a[2] < b[2];});
        kruskal(n, edges);
        return {move(ke), move(nke)};
    }
};

class SolutionV3 {///24ms 100.00% 12.6M 31.82%
    using vi = vector<int>;
    using pii = pair<int,int>;
    using si = unordered_set<int>;
    using psi = pair<si,int>;

    vector<vi> graph;
    vi level;
    unordered_map<int, int> cfa;

    class UFSet
    {
        vi father, level;
    public:
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
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




    int hpii (int a, int b)
    {
        return a * 10000 + b;
    }
    int commonFather (int i, int j)
    {
        if (i == j) return i;
        if (level[j] < level[i]) swap(i, j);
        if (!level[i]) return i;
        if (cfa.count(hpii(i,j))) return cfa[hpii(i,j)];
        if (level[i] == level[j]) return cfa[hpii(i,j)] = commonFather(graph[i][0], graph[j][0]);
        return cfa[hpii(i,j)] = commonFather(i, graph[j][0]);
    }

    pair<int, vi> kruskal (int n, vector<vi> & edges)
    {
        UFSet ufs(n);
        int m = edges.size();
        vi rst(m, 0);
        int tot = 0, cnt = 1;
        FOR(i,m)
        {
            vi & e = edges[i];
            if (ufs.same(e[0], e[1])) continue;
            ufs.unite(e[0], e[1]), rst[i] = 1, tot += e[2], ++cnt;
            if (cnt == n) break;
        }
        return {cnt == n ? tot : -1, rst};
    }

    void dfs (vector<vi> & g, vector<vector<int>>& edges, vi & vst, int now = 0)
    {
        for (int i : g[now])
        {
            vi & e = edges[i];
            int next = e[0] == now ? e[1] : e[0];
            if (vst[next]) continue;
            vst[next] = 1;
            level[next] = level[now] + 1;
            graph[next] = vi{now, e[2], i};
            dfs(g, edges, vst, next);
        }
    }

    void createTree (int n, vi & es, vector<vector<int>>& edges)
    {
        vi vst(n, 0);
        vst[0] = 1;
        vector<vi> g(n, vi{});
        FOR(i,edges.size()) if(es[i]) g[edges[i][0]].emplace_back(i), g[edges[i][1]].emplace_back(i);
        dfs(g, edges, vst);
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        FOR(i,m) edges[i].emplace_back(i);
        sort(begin(edges), end(edges), [](vi & a, vi & b){return a[2] < b[2];});

        graph = vector<vi>(n, vi{});
        level = vi(n, 0);
        auto [tot, v] = kruskal(n, edges);

        createTree(n, v, edges);

        vi nk(m, 0);
        FOR(i,m)if(!v[i])
        {
            vi & e = edges[i];
            int cf = commonFather(e[0], e[1]);
            for (int now = e[0]; now != cf; now = graph[now][0])
                if (graph[now][1] == e[2])
                    nk[graph[now][2]] = 1, nk[i] = 1;

            for (int now = e[1]; now != cf; now = graph[now][0])
                if (graph[now][1] == e[2])
                    nk[graph[now][2]] = 1, nk[i] = 1;
        }

        vi ke, nke;
        FOR(i,m)
        {
            if (nk[i]) nke.emplace_back(edges[i].back());
            else if (v[i]) ke.emplace_back(edges[i].back());
        }
        return {ke, nke};
    }
};

class SolutionV2 {///76ms 67.16% 16.1M 16.66%
    using vi = vector<int>;
    using pii = pair<int,int>;
    using si = unordered_set<int>;
    using psi = pair<si,int>;

    class UFSet
    {
        vi father, level;
    public:
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
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

    pair<int, vi> kruskal (int n, vector<vi> & edges)
    {
        UFSet ufs(n);
        int m = edges.size();
        vi rst(m, 0);
        int tot = 0, cnt = 1;
        FOR(i,m)
        {
            vi & e = edges[i];
            if (ufs.same(e[0], e[1])) continue;
            ufs.unite(e[0], e[1]), rst[i] = 1, tot += e[2], ++cnt;
            if (cnt == n) break;
        }
        return {cnt == n ? tot : -1, rst};
    }
    int kruskalRm (int n, vector<vi> & edges, int ie)
    {
        UFSet ufs(n);
        int m = edges.size();
        int tot = 0, cnt = 1;
        FOR(i,m) if (i != ie)
        {
            vi & e = edges[i];
            if (ufs.same(e[0], e[1])) continue;
            ufs.unite(e[0], e[1]), tot += e[2], ++cnt;
            if (cnt == n) break;
        }
        return cnt == n ? tot : -1;
    }
    int kruskalAd (int n, vector<vi> & edges, int ie)
    {
        UFSet ufs(n);
        ufs.unite(edges[ie][0], edges[ie][1]);
        int m = edges.size();
        int tot = edges[ie][2], cnt = 2;
        FOR(i,m)
        {
            vi & e = edges[i];
            if (ufs.same(e[0], e[1])) continue;
            ufs.unite(e[0], e[1]), tot += e[2], ++cnt;
            if (cnt == n) break;
        }
        return cnt == n ? tot : -1;
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        FOR(i,m) edges[i].emplace_back(i);
        sort(begin(edges), end(edges), [](vi & a, vi & b){return a[2] < b[2];});
        auto [tot, v] = kruskal(n, edges);
        vi ke, nke;
        FOR(i,m)
        {
            if (v[i] && kruskalRm(n, edges, i) != tot) ke.emplace_back(edges[i].back());
            else if (v[i] || kruskalAd(n, edges, i) == tot) nke.emplace_back(edges[i].back());
        }
        return {ke, nke};
    }
};


///python.set.__sub__
template <typename T>
unordered_set<T> operator - (const unordered_set<T> & self, const unordered_set<T> & value)
{
    unordered_set<T> res;
    for (typename unordered_set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
        if (value.find(*it) == value.end())
            res.insert(*it);
    return res;
}

///python.set.__iand__
template <typename T>
unordered_set<T> & operator &= (unordered_set<T> & self, const unordered_set<T> & value)
{
    unordered_set<T> tmp = self - value;
    for (typename unordered_set<T>::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
        self.erase(*it);
    return self;
}



///python.set.__ior__
template <typename T>
unordered_set<T> & operator |= (unordered_set<T> & self, const unordered_set<T> & value)
{
    for (typename unordered_set<T>::const_iterator it = value.begin(); it != value.end(); ++it)
        self.insert(*it);
    return self;
}

class SolutionV1 {///TLE
    using vi = vector<int>;
    using pii = pair<int,int>;
    using si = unordered_set<int>;
    using psi = pair<si,int>;
    vector<psi> rst;
    int n;
    int prim (vector<vector<vi>> & graph, priority_queue<vi> pq, vi vst, si es, int tot = 0, int cnt = 1, int w = 0)
    {
        while (!pq.empty())
        {
            auto v = pq.top(); pq.pop();///[weight, iEdge, to]
            if (vst.at(v.at(2))) continue;
            if (w && v.at(0) != w) return 0;
            if (!pq.empty() && pq.top().at(0) == v.at(0)) prim(graph, pq, vst, es, tot, cnt, v.at(0));
            tot += v.at(0), ++cnt, w = 0, es.insert(v.at(1)), vst.at(v.at(2)) = 1;
            if (cnt == n)
            {
                rst.emplace_back(psi{es, tot});
                return tot;
            }
            for (auto & x : graph.at(v.at(2))) if (!vst.at(x.at(2)))
                pq.push(x);
        }
        return tot;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        this->n = n;
        vector<vector<vi>> graph(n, vector<vi>());
        FOR(i,edges.size())
        {
            vi & e = edges.at(i);
            graph.at(e.at(0)).emplace_back(vi{-e.at(2), i, e.at(1)});
            graph.at(e.at(1)).emplace_back(vi{-e.at(2), i, e.at(0)});
        }

        priority_queue<vi> pq;
        vi vst(n, 0);
        vst.at(0) = 1;
        for (auto & x : graph.at(0)) pq.push(x);
        int tot = prim(graph, move(pq), move(vst), si());
        unordered_set<int> ke = rst.back().first, nke;
        for (auto & [x, y] : rst) if (y == tot) ke &= x;
        for (auto & [x, y] : rst) if (y == tot) nke |= (x - ke);
        return vector<vi>{vi(begin(ke), end(ke)), vi(begin(nke), end(nke))};
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<int,vector<vi>>> xs{
        {5, {{0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,4,3},{3,4,3},{1,4,6}}},
        {4,{{0,1,1},{1,2,1},{2,3,1},{0,3,1}}}
    };
    for (auto &[x,y] : xs)
        print(x,y), print(Solution().findCriticalAndPseudoCriticalEdges(x,y)), print("===");
    return 0;
}
#endif
