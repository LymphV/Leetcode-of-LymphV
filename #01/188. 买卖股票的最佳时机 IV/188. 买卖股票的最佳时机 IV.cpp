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
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1：

输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
示例 2：

输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 

提示：

0 <= k <= 109
0 <= prices.length <= 1000
0 <= prices[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 99.14% 10.9M 95.73%
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;

        k = min(k, n / 2) + 1;
        int buy[k], sell[k];
        buy[0] = 0, sell[0] = 0, buy[1] = -prices[0];

        int p = 2, q = 1;
        ffor(i,1,n)
        {
            for (int j = 0; j + 1 < k && j < q; ++j)
            {
                int t = sell[j] - prices[i];
                if (j + 1 < p) buy[j + 1] = max(t, buy[j + 1]);
                else if (buy[j] < t) buy[j + 1] = t, ++p;
            }
            ffor(j,1,p)
            {
                int t = buy[j] + prices[i];
                if (j < q) sell[j] = max(t, sell[j]);
                else if (sell[j - 1] < t) sell[j] = t, ++q;
            }
        }
        return sell[q - 1];
    }
};


class SolutionV7 {///4ms 99.14% 10.9M 93.83%
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;

        k = min(k, n / 2) + 1;
        int buy[k], sell[k];
        FOR(i,k) buy[i] = sell[i] = -1000000;
        buy[0] = 0, sell[0] = 0, buy[1] = -prices[0];

        ffor(i,1,n) ffor(j,1,k)
        {
            buy[j] = max(sell[j - 1] - prices[i], buy[j]);
            sell[j] = max(buy[j] + prices[i], sell[j]);
        }
        return sell[k - 1];
    }
};



class SolutionV6 {///12ms 70.68% 10.9M 96.68%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vi buy{0, -prices[0]}, sell{0};
        ffor(i,1,n)
        {
            for (int j = 0, m = sell.size(); j < m && j < k; ++j)
            {
                int t = sell[j] - prices[i];
                if (j + 1 < buy.size()) buy[j + 1] = max(t, buy[j + 1]);
                else if (buy .back() < t) buy.emplace_back(t);
            }
            ffor(j,1,buy.size())
            {
                int t = buy[j] + prices[i];
                if (j < sell.size()) sell[j] = max(t, sell[j]);
                else if (sell.back() < t) sell.emplace_back(t);
            }
        }
        return sell.back();
    }
};

class SolutionV5 {///36ms 34.98% 14.9M 24.74%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vi buy{0, -prices[0]}, sell{0}, b, s;
        ffor(i,1,n)
        {
            b = vi{0}, s = vi{0};
            for (int j = 0, m = sell.size(); j < m && j < k; ++j)
            {
                int t = sell[j] - prices[i];
                if (j + 1 < buy.size()) b.emplace_back(max(t, buy[j + 1]));
                else if (b.back() < t) b.emplace_back(t);
            }
            ffor(j,1,buy.size())
            {
                int t = buy[j] + prices[i];
                if (j < sell.size()) s.emplace_back(max(t, sell[j]));
                else if (s.back() < t) s.emplace_back(t);
            }
            buy = move(b), sell = move(s);
        }

        return sell.back();
    }
};


class SolutionV4 {///32ms 35.84% 14.9M 24.83%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vi buy{0, -prices[0]}, sell{0}, b, s;
        ffor(i,1,n)
        {
            b = vi{0}, s = vi{0};
            for (int j = 0, m = sell.size(); j < m && j < k; ++j)
            {
                int t = sell[j] - prices[i];
                if (j + 1 < buy.size()) b.emplace_back(max(t, buy[j + 1]));
                else if (b.back() < t) b.emplace_back(t);
            }
            ffor(j,1,buy.size())
            {
                int t = buy[j] + prices[i];
                if (j < sell.size()) s.emplace_back(max(t, sell[j]));
                else if (s.back() < t) s.emplace_back(t);
            }
            buy = move(b), sell = move(s);
        }

        return *max_element(begin(sell), end(sell));
    }
};

class SolutionV3 {///32ms 35.84% 15.1M 24.46%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vi buy{0, -prices[0]}, sell{0}, b, s;
        ffor(i,1,n)
        {
            b = vi{0}, s = vi{0};
            for (int j = 0, m = sell.size(); j < m && j < k; ++j)
                b.emplace_back(max(sell[j] - prices[i], j + 1 < buy.size() ? buy[j + 1] : -1000000));
            ffor(j,1,buy.size())
                s.emplace_back(max(buy[j] + prices[i], j < sell.size() ? sell[j] : -1000000));
            buy = move(b), sell = move(s);
        }

        return *max_element(begin(sell), end(sell));
    }
};

class SolutionV2 {///32ms 35.84% 15.4M 23.67%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vi buy{0, -prices[0]}, sell{0}, b, s;
        ffor(i,1,n)
        {
            b = vi{0}, s = vi{0};
            for (int j = 0, m = sell.size(); j < m && j < k; ++j)
                b.emplace_back(max(sell[j] - prices[i], j + 1 < buy.size() ? buy[j + 1] : -1000000));
            ffor(j,1,buy.size())
                s.emplace_back(max(buy[j] + prices[i], j < sell.size() ? sell[j] : -1000000));
            buy = b, sell = s;
        }

        return *max_element(begin(sell), end(sell));
    }
};

class SolutionV1 {///32ms 35.84% 15.6M 23.62%
    using vi = vector<int>;
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n < 2 || !k) return 0;
        vector<vi> buy(n, vi{0}), sell(n, vi{0});
        buy[0].emplace_back(-prices[0]);
        ffor(i,1,n)
        {
            for (int j = 0, m = sell[i - 1].size(); j < m && j < k; ++j)
                buy[i].emplace_back(max(sell[i - 1][j] - prices[i], j + 1 < buy[i - 1].size() ? buy[i - 1][j + 1] : -1000000));
            ffor(j,1,buy[i - 1].size())
                sell[i].emplace_back(max(buy[i - 1][j] + prices[i], j < sell[i - 1].size() ? sell[i - 1][j] : -1000000));
        }


        return *max_element(begin(sell.back()), end(sell.back()));
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<int,vi>> xs{
        {2, {2,1,4,5,2,9,7}},
        {
            2,{3,2,6,5,0,3}
        }
    };
    for (auto & [x,y] : xs)
        print(x,y), print(Solution().maxProfit(x,y)), print("===");
    return 0;
}
#endif
