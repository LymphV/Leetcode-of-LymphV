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
给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边 。

第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。

返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

示例 1:

输入: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
输出: [8,12,6,10,10,10]
解释:
如下为给定的树的示意图：
  0
 / \
1   2
   /|\
  3 4 5

我们可以计算出 dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
也就是 1 + 1 + 2 + 2 + 2 = 8。 因此，answer[0] = 8，以此类推。
说明: 1 <= N <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-distances-in-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///边号
class Solution///184ms 30.71% 30.4M 18.28%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vector<pii>> es;
    vector<pii> dis;///edge->(dis,size)


    pii dp (int father, int root, int e)
    {
        if (dis[e].second) return dis[e];

        int rst = 0, sz = 1;
        for (auto [son, e] : es[root])
        if (son != father)
        {
            auto [d, s] = dp(root, son, e);
            rst += d + s, sz += s;
        }
        return dis[e] = pii(rst, sz);
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N);
        dis.resize(3 * N);
        int k = N - 1;
        for (auto e : edges)
        {
            es[e[0]].emplace_back(pii(e[1], ++k));
            es[e[1]].emplace_back(pii(e[0], ++k));
        }
        vi rst;
        FOR(i,N) rst.emplace_back(dp(-1,i,i).first);
        return rst;
    }
};


///换根，不拷贝数组
class SolutionV5///156ms 67.83% 28.8M 19.35%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vi> es;
    vi rst;
    vi dis;
    vi size;

    void dfs (int root, int father = -1)
    {
        int & rst = dis[root], & sz = size[root];
        for (auto son : es[root])
        if (son != father)
        {
            dfs(son, root);
            rst += dis[son] + size[son], sz += size[son];
        }
    }

    void swapRoot (int root, int father = -1)
    {
        if (0 <= father)
        {
            int sf = size[father], df = dis[father], sr = size[root], dr = dis[root];
            size[father] -= size[root], dis[father] -= size[root] + dis[root];
            size[root] += size[father], dis[root] += size[father] + dis[father];
            rst[root] = dis[root];
            for (auto son : es[root])
            if (son != father)
                swapRoot(son, root);
            size[father] = sf, dis[father] = df, size[root] = sr, dis[root] = dr;
        }
        else
        {
            rst[root] = dis[root];
            for (auto son : es[root])
            if (son != father)
                swapRoot(son, root);
        }
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N), rst.resize(N), dis.resize(N, 0), size.resize(N, 1);
        for (auto e : edges)
            es[e[0]].emplace_back(e[1]), es[e[1]].emplace_back(e[0]);

        dfs(0);
        swapRoot(0);
        return rst;
    }
};



///换根
class SolutionV4///1396ms 5.59% 348.8M 5.37%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vi> es;
    vi rst;
    vi dis;
    vi size;

    pii dfs (int root, int father = -1)
    {
        int rst = 0, sz = 1;
        for (auto son : es[root])
        if (son != father)
        {
            auto [d, s] = dfs(son, root);
            rst += d + s, sz += s;
        }
        dis[root] = rst, size[root] = sz;
        return pii(rst, sz);
    }

    vi swapRoot (int root, vi dis, vi size, int father = -1)
    {
        if (0 <= father)
        {
            size[father] -= size[root], dis[father] -= size[root] + dis[root];
            size[root] += size[father], dis[root] += size[father] + dis[father];
        }
        rst[root] = dis[root];
        for (auto son : es[root])
        if (son != father)
            swapRoot(son, dis, size, root);
        return rst;
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N), rst.resize(N), dis.resize(N), size.resize(N);
        for (auto e : edges)
            es[e[0]].emplace_back(e[1]), es[e[1]].emplace_back(e[0]);

        dfs(0);
        return swapRoot(0, dis, size);
    }
};

///emplace_back
class SolutionV3///480ms 5.59% 51.3M 5.37%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vi> es;
    unordered_map<int, unordered_map<int,pii>> dis;///(father,root)->(dis,size)


    pii dp (int father, int root)
    {
        if (dis.count(father) && dis[father].count(root)) return dis[father][root];

        int rst = 0, sz = 1;
        for (auto son : es[root])
        if (son != father)
        {
            auto [d, s] = dp(root, son);
            rst += d + s, sz += s;
        }
        return dis[father][root] = pii(rst, sz);
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N);
        for (auto e : edges)
            es[e[0]].emplace_back(e[1]), es[e[1]].emplace_back(e[0]);
        vi rst;
        FOR(i,N) rst.emplace_back(dp(N,i).first);
        return rst;
    }
};

///哈希
class SolutionV2///540ms 5.59% 51.7M 5.37%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vi> es;
    unordered_map<int, unordered_map<int,pii>> dis;///(father,root)->(dis,size)


    pii dp (int father, int root)
    {
        if (dis.count(father) && dis[father].count(root)) return dis[father][root];

        int rst = 0, sz = 1;
        for (auto son : es[root])
        if (son != father)
        {
            auto [d, s] = dp(root, son);
            rst += d + s, sz += s;
        }
        return dis[father][root] = pii(rst, sz);
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N);
        for (auto e : edges)
            es[e[0]].push_back(e[1]), es[e[1]].push_back(e[0]);
        vi rst;
        FOR(i,N) rst.push_back(dp(N,i).first);
        return rst;
    }
};

///红黑树
class SolutionV1///600ms 5.59% 40.6M 5.37%
{
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<vi> es;
    map<pii, pii> dis;///(father,root)->(dis,size)


    pii dp (int father, int root)
    {
        if (dis.count(pii(father,root))) return dis[pii(father,root)];

        int rst = 0, sz = 1;
        for (auto son : es[root])
        if (son != father)
        {
            auto [d, s] = dp(root, son);
            rst += d + s, sz += s;
        }
        return dis[pii(father,root)] = pii(rst, sz);
    }
public:
    vi sumOfDistancesInTree(int N, vector<vi>& edges)
    {
        es.resize(N);
        for (auto e : edges)
            es[e[0]].push_back(e[1]), es[e[1]].push_back(e[0]);
        vi rst;
        print (dp(0,1));
        FOR(i,N) rst.push_back(dp(-1,i).first);
        return rst;
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<pair<int,vector<vi>>> xs{
        {6, {{0,1},{0,2},{2,3},{2,4},{2,5}}}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().sumOfDistancesInTree(x,y));
    return 0;
}
#endif
