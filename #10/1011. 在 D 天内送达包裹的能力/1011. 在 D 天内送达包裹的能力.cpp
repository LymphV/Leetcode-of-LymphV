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
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。

传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。

返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

 

示例 1：

输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
输出：15
解释：
船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
第 1 天：1, 2, 3, 4, 5
第 2 天：6, 7
第 3 天：8
第 4 天：9
第 5 天：10

请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的。
示例 2：

输入：weights = [3,2,2,4,1,4], D = 3
输出：6
解释：
船舶最低载重 6 就能够在 3 天内送达所有包裹，如下所示：
第 1 天：3, 2
第 2 天：2, 4
第 3 天：1, 4
示例 3：

输入：weights = [1,2,3,1,1], D = 4
输出：3
解释：
第 1 天：1
第 2 天：2
第 3 天：3
第 4 天：1, 1
 

提示：

1 <= D <= weights.length <= 50000
1 <= weights[i] <= 500

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///96ms 8.51% 25.6M 19.94%
    using vi = vector<int>;

    bool judge (vi & weights, int D, int cap, int * tot)
    {
        int i = 0, n = weights.size();
        for (int d = 1; d <= D; ++d)
        {
            int l = i, r = n;
            while (l < r)
            {
                int m = l + (r + 1 - l) / 2;
                if (cap < tot[m] - tot[i]) r = m - 1;
                else l = m;
            }
            if ((i = l) == n) break;
        }
        return n <= i;
    }
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n = weights.size();
        int tot[n + 1];
        tot[0] = 0;
        partial_sum(begin(weights), end(weights), tot + 1);
        int left = 0, right = 0;
        for (int w : weights) left = max(left, w), right += w;
        while (left < right)
        {
            int m = left + (right - left) / 2;
            if (judge(weights,D,m,tot)) right = m;
            else left = m + 1;
        }
        return left;
    }
};

class SolutionV1 {///76ms 27.79% 25.3M 89.32%
    using vi = vector<int>;

    bool judge (vi & weights, int D, int cap)
    {
        int d = 1;
        for (int i = 0, now = 0, n = weights.size(); i < n; ++i)
        {
            if (cap < now + weights[i])
            {
                if (D < ++d) return 0;
                now = weights[i];
            }
            else now += weights[i];
        }
        return 1;
    }
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n = weights.size();
        int left = 0, right = 0;
        for (int w : weights) left = max(left, w), right += w;
        while (left < right)
        {
            int m = left + (right - left) / 2;
            if (judge(weights,D,m)) right = m;
            else left = m + 1;
        }
        return left;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{1,2,3,4,5,6,7,8,9,10},5},
    };
    for (auto & [x, y] : xs)
        print(x,y), print(Solution().shipWithinDays(x, y)), print("===");
    return 0;
}
#endif
