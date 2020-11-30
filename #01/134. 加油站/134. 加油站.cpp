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
在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明: 

如果题目有解，该答案即为唯一答案。
输入数组均为非空数组，且长度相同。
输入数组中的元素均为非负数。
示例 1:

输入:
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

输出: 3

解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
示例 2:

输入:
gas  = [2,3,4]
cost = [3,4,3]

输出: -1

解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/gas-station
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)



#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///记录最小油
class Solution {///4ms 99.45% 10.1M 5.23%
    using vi = vector<int>;
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        if (!n) return -1;
        vi v(n);
        FOR(i,n) v[i] = gas[i] - cost[i];
        if (n == 1) return 0 <= v[0] ? 0 : -1;
        vi start0(n, 0), end0(n, 0), left0(n, 0);///start0 记最小油， end0记最小油，left0记到0剩油
        for (int i = 1, now = 0; i < n; ++i)
        {
            now += v[i - 1];
            start0[i] = min(start0[i - 1], now);
        }
        end0[n - 1] = min(0, v[n - 1]), left0[n - 1] = v[n - 1];
        for (int i = n - 2; i; --i)
        {
            left0[i] = v[i] + left0[i + 1];
            end0[i] = min(v[i], v[i] + end0[i + 1]);
        }

        if (0 <= v[0] && 0 <= v[0] + end0[1]) return 0;

        ffor(i,1,n) if (0 <= end0[i] && 0 <= left0[i] + start0[i]) return i;
        return -1;
    }
};

///纯暴力，提前做减法
class SolutionV2 {///176ms 25.79% 10M 5.23%
    using vi = vector<int>;
    bool check(int i, int n, vi & v)
    {
        int now = 0;
        ffor(j,i,i+n)
        {
            int k = j % n;
            now += v[k];
            if (now < 0) return 0;
        }
        return 1;
    }

public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vi v(n);
        FOR(i,n) v[i] = gas[i] - cost[i];
        FOR(i,n) if (check(i,n,v)) return i;
        return -1;
    }
};

///纯暴力
class SolutionV1 {///224ms 19.26% 9.9M 11.22%
    bool check(int i, int n, vector<int>& gas, vector<int>& cost)
    {
        int now = 0;
        ffor(j,i,i+n)
        {
            int k = j % n;
            now += gas[k] - cost[k];
            if (now < 0) return 0;
        }
        return 1;
    }

public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        FOR(i,n) if (check(i,n,gas,cost)) return i;
        return -1;
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
