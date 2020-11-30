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
给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:

num 的长度小于 10002 且 ≥ k。
num 不会包含任何前导零。
示例 1 :

输入: num = "1432219", k = 3
输出: "1219"
解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。
示例 2 :

输入: num = "10200", k = 1
输出: "200"
解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。
示例 3 :

输入: num = "10", k = 2
输出: "0"
解释: 从原数字移除所有的数字，剩余为空就是0。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-k-digits
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


///单调栈
class Solution { ///4ms 94.78% 6.9M 58.48%, 0ms 100.00% 7.1M 38.17%
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (!k) return num;
        if (k == n) return "0";
        auto l = begin(num), i = begin(num), j = begin(num), r = end(num);
        for (; j != r; ++j)
        {
            print (string(l,i), string(j,r), k);
            while (k && i != l && *j < *(i - 1)) --i, --k;
            if (!k) break;
            if (i != l || *j != '0') *(i++) = *j;
        }
        if (k) i -= k;
        if (i == l) while (j != r && *j == '0') ++j;
        return (i - l) + (r - j) ? string(l, i) + string(j, r) : "0";
    }
};


///优先队列,with 提前终止0优化
class SolutionV4 { ///4ms 94.78% 7.8M 14.59%
    using pit = pair<int, string::iterator>;
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (!k) return num;
        if (k == n) return "0";
        string rst;
        auto l = begin(num), now = begin(num), r = end(num);
        priority_queue<pit,vector<pit>,greater<pit>> pq;
        while (k)
        {
            if (r - l == k)
            {
                l = r, k = 0;
                break;
            }
            for (; now != l + k + 1 && now != r; ++now)
            {
                pq.push({*now, now});
                if (!*now) break;
            }
            for(;;)
            {
                auto [i, t] = pq.top(); pq.pop();
                if (t < l) continue;
                k -= t - l;
                l = t;
                break;
            }
            if (rst.size() || *l != '0') rst += *l;
            ++l;
        }
        rst += string(l, end(num));
        return rst.size() ? rst : "0";
    }
};

///优先队列
class SolutionV3 { ///4ms 94.78% 7.9M 13.79%
    using pit = pair<int, string::iterator>;
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (!k) return num;
        if (k == n) return "0";
        string rst;
        auto l = begin(num), now = begin(num), r = end(num);
        priority_queue<pit,vector<pit>,greater<pit>> pq;
        while (k)
        {
            if (r - l == k)
            {
                l = r, k = 0;
                break;
            }
            for (; now != l + k + 1 && now != r; ++now) pq.push({*now, now});
            for(;;)
            {
                auto [i, t] = pq.top(); pq.pop();
                if (t < l) continue;
                k -= t - l;
                l = t;
                break;
            }
            if (rst.size() || *l != '0') rst += *l;
            ++l;
        }
        rst += string(l, end(num));
        return rst.size() ? rst : "0";
    }
};


///暴力
class SolutionV2 { ///72ms 9.11% 7.2M 35.03%
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (!k) return num;
        if (k == n) return "0";
        string rst;
        auto i = begin(num), r = end(num);
        while (k)
        {
            if (r - i == k)
            {
                i = r, k = 0;
                break;
            }
            auto j = min_element(i, i + k + 1);
            rst += *j;
            k -= j - i;
            i = j + 1;
        }
        rst += string(i, end(num));
        i = begin(rst), r = end(rst);
        while (*i == '0' && 1 < r - i) ++i;
        return string(i,r);
    }
};

///暴力
class SolutionV1 { ///68ms 10.23% 7.1M 39.31%
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (!k) return num;
        if (k == n) return "0";
        string rst;
        auto i = begin(num), r = end(num);
        while (k)
        {
            if (r - i == k)
            {
                i = r, k = 0;
                break;
            }
            auto j = min_element(i, i + k + 1);
            if (rst.size() || *j != '0') rst += *j;
            k -= j - i;
            i = j + 1;
        }
        rst += string(i, end(num));
        return rst.size() ? rst : "0";
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string,int>> xs{
        {"1107", 1},
        {"1432219", 3},
        {"10200", 1},
        {"112",1}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().removeKdigits(x,y)), print("===");
    return 0;
}
#endif
