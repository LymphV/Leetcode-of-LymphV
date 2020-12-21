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
给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

示例 1:

输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
输出: 8
解释: 能够达到的最大利润:
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
注意:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///184ms 98.01% 51M 50.05%
    using vi = vector<int>;
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n < 2) return 0;
        int buy = -prices[0] - fee, sell = 0;
        ffor(i,1,n)
        {
            int b = -prices[i] - fee + sell, s = prices[i] + buy;
            buy = max(buy, b), sell = max(sell, s);
        }
        return sell;
    }
};

class SolutionV1 {///TLE
    using vi = vector<int>;
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size(), rst = 0;
        if (n < 2) return 0;
        vi buy(n, 0), sell(n, 0);
        buy[0] = -prices[0] - fee;
        ffor(i,1,n)
        {
            buy[i] = -prices[i] - fee + *max_element(begin(sell), begin(sell) + i);
            sell[i] = prices[i] + *max_element(begin(buy), begin(buy) + i);
            rst = max(rst, sell[i]);
        }
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{1, 3, 2, 8, 4, 9}, 2}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().maxProfit(x, y)), print("===");
    return 0;
}
#endif
