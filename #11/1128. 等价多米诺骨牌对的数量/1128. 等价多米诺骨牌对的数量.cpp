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
给你一个由一些多米诺骨牌组成的列表 dominoes。

如果其中某一张多米诺骨牌可以通过旋转 0 度或 180 度得到另一张多米诺骨牌，我们就认为这两张牌是等价的。

形式上，dominoes[i] = [a, b] 和 dominoes[j] = [c, d] 等价的前提是 a==c 且 b==d，或是 a==d 且 b==c。

在 0 <= i < j < dominoes.length 的前提下，找出满足 dominoes[i] 和 dominoes[j] 等价的骨牌对 (i, j) 的数量。

 

示例：

输入：dominoes = [[1,2],[2,1],[3,4],[5,6]]
输出：1
 

提示：

1 <= dominoes.length <= 40000
1 <= dominoes[i][j] <= 9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-equivalent-domino-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///36ms 94.38% 16.8M 83.24%
    using vi = vector<int>;
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        vi cnt(100, 0);
        int rst = 0;
        for (vi & v : dominoes)
        {
            if (v[1] < v[0]) swap(v[0], v[1]);
            int & c = cnt[10 * v[0] + v[1]];
            rst += c;
            ++c;
        }
        return rst;
    }
};

namespace std
{
    template<class T1, class T2>
    struct hash<pair<T1,T2>>///哈希的模板定制
    {
    public:
        std::size_t operator () (const pair<T1, T2> & p) const
        {
            return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
        }

    };
}

class SolutionV2 {///36ms 99.48% 16.7M 99.74%
    using pii = pair<int,int>;
    using vi = vector<int>;
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<pii,int> cnt;
        int rst = 0;
        for (vi & v : dominoes)
        {
            if (v[1] < v[0]) swap(v[0], v[1]);
            int & c = cnt[pii{v[0],v[1]}];
            rst += c;
            ++c;
        }
        return rst;
    }
};


class SolutionV1 {///40ms 98.45% 16.8M 97.14%
    using pii = pair<int,int>;
    using vi = vector<int>;
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<pii,int> cnt;
        int rst = 0;
        for (vi & v : dominoes)
        {
            if (v[1] < v[0]) swap(v[0], v[1]);
            rst += (cnt[pii{v[0],v[1]}]++);
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
