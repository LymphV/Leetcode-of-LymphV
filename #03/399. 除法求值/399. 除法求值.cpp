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
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。

 

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

 

示例 1：

输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
示例 2：

输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]
示例 3：

输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]
 

提示：

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj 由小写英文字母与数字组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/evaluate-division
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 8.5M 30.60%
    using vi = vector<int>;
    using pid = pair<int,double>;


    double bfs (vector<vector<pid>> & graph, int a, int b)
    {
        if (a == b) return 1;
        queue<pid> q;
        vi cnt(graph.size(), 0);
        q.push({a, 1});
        cnt[a] = 1;
        while (!q.empty())
        {
            auto [now, value] = q.front(); q.pop();
            for (auto [next, v] : graph[now])
            {
                if (cnt[next]) continue;
                if (next == b) return value * v;
                q.push({next, value * v});
                cnt[next] = 1;
            }
        }
        return -1;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        if (queries.empty()) return {};
        unordered_map<string,int> s2i;

        for (auto & x : equations) for (auto & y : x)
            if (!s2i.count(y))
                s2i[y] = s2i.size();

        vector<vector<pid>> graph(s2i.size(), vector<pid>{});

        FOR(i,equations.size())
        {
            int a = s2i[equations[i][0]], b = s2i[equations[i][1]];
            double v = values[i];
            graph[a].emplace_back(pid{b, v});
            graph[b].emplace_back(pid{a, 1 / v});
        }

        vector<double> rst;

        for (auto & x :queries)
        {
            if (!s2i.count(x[0]) || !s2i.count(x[1]))
            {
                rst.emplace_back(-1);
                continue;
            }
            rst.emplace_back(bfs(graph, s2i[x[0]], s2i[x[1]]));
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
