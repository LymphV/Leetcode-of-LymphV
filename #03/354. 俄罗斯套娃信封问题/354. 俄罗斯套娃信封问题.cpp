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
给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。

说明:
不允许旋转信封。

示例:

输入: envelopes = [[5,4],[6,4],[6,7],[2,3]]
输出: 3
解释: 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/russian-doll-envelopes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///52ms 87.63% 15.7M 20.17%
    using vi = vector<int>;
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(begin(envelopes), end(envelopes), [](const vi & a, const vi & b)
             {
                 return a[0] < b[0] || a[0] == b[0] && b[1] < a[1];
             });
        int n = envelopes.size();
        if (!n) return 0;
        vi rst;
        FOR(i,n)
        {
            auto it = lower_bound(begin(rst), end(rst), envelopes[i][1]);
            if (it == end(rst)) rst.emplace_back(envelopes[i][1]);
            else *it = envelopes[i][1];
        }
        return rst.size();
    }
};

class SolutionV2 {///1064ms 49.28% 15.9M 19.42%
    using vi = vector<int>;
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(begin(envelopes), end(envelopes), [](const vi & a, const vi & b)
             {
                 return a[0] < b[0] || a[0] == b[0] && b[1] < a[1];
             });
        int n = envelopes.size();
        if (!n) return 0;
        vi rst(n, 1);
        FOR(i,n) FOR(j,i) if (envelopes[j][1] < envelopes[i][1])
            rst[i] = max(rst[i], rst[j] + 1);
        return *max_element(begin(rst), end(rst));
    }
};


class SolutionV1 {///1360ms 24.73% 13.3M 88.51%
    using vi = vector<int>;
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(begin(envelopes), end(envelopes));
        int n = envelopes.size();
        if (!n) return 0;
        vi rst(n, 1);
        FOR(i,n) FOR(j,i) if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
            rst[i] = max(rst[i], rst[j] + 1);
        return *max_element(begin(rst), end(rst));
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{5,4},{6,4},{6,7},{2,3}}
    };
    for (auto & x : xs)
        print(x), print(Solution().maxEnvelopes(x)), print("===");
    return 0;
}
#endif
