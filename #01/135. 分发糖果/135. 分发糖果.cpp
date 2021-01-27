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
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

你需要按照以下要求，帮助老师给这些孩子分发糖果：

每个孩子至少分配到 1 个糖果。
相邻的孩子中，评分高的孩子必须获得更多的糖果。
那么这样下来，老师至少需要准备多少颗糖果呢？

示例 1:

输入: [1,0,2]
输出: 5
解释: 你可以分别给这三个孩子分发 2、1、2 颗糖果。
示例 2:

输入: [1,2,2]
输出: 4
解释: 你可以分别给这三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这已满足上述两个条件。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/candy
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///44ms 59.76% 17.5M 8.46%
    using vi = vector<int>;
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (!n) return 0;
        if (n == 1) return 1;

        vi a(n, 1), b(n, 1);

        ffor(i,1,n)
        {
            if (ratings[i - 1] < ratings[i]) a[i] = a[i - 1] + 1;
            if (ratings[n - i] < ratings[n - i - 1]) b[n - i - 1] = b[n - i] + 1;
        }
        int rst = 0;
        FOR(i,n) rst += max(a[i], b[i]);

        return rst;
    }
};

///拓扑排序
class SolutionV1 {///108ms 5.31% 25M 5.04%
    using vi = vector<int>;
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (!n) return 0;
        if (n == 1) return 1;
        vi in(n, 0), cnd(n, 1);
        vector<vi> out(n);

        auto addEdge = [&](int i, int j)
        {
            if (ratings[i] < ratings[j]) ++in[j], out[i].emplace_back(j);
        };

        addEdge(0, 1), addEdge(n - 1, n - 2);
        ffor(i,1,n-1) addEdge(i, i - 1), addEdge(i, i + 1);

        queue<int> q;
        FOR(i,n) if (!in[i]) q.push(i);
        int rst = 0;
        while(!q.empty())
        {
            int i = q.front(); q.pop();
            rst += cnd[i];

            for (int x : out[i])
            {
                if (!--in[x]) q.push(x);
                cnd[x] = max(cnd[x], cnd[i] + 1);
            }
        }

        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,0,2},
        {1,2,2}
    };
    for (auto x : xs)
        print(x), print(Solution().candy(x)), print("===");
    return 0;
}
#endif
