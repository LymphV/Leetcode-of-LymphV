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
给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。

若可行，输出任意可行的结果。若不可行，返回空字符串。

示例 1:

输入: S = "aab"
输出: "aba"
示例 2:

输入: S = "aaab"
输出: ""
注意:

S 只包含小写字母并且长度在[1, 500]区间内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reorganize-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///0ms 100.00% 8.1M 5.13%
    using vi = vector<int>;
    using pic = pair<int,char>;
public:
    string reorganizeString(string S) {
        int N = 26, n = S.size();
        if (n <= 1) return S;
        vi cnt(N, 0);
        for (char c : S) ++cnt[c - 'a'];
        vector<pic> order;
        FOR(i,N) if(cnt[i]) order.emplace_back(pic(cnt[i],'a' + i));
        auto maxE = max_element(begin(order), end(order));
        if (n + 1 < maxE->first * 2) return "";

        int no = order.size(), m = maxE->first;
        vector<string> rst(m, string(1, maxE->second));
        int i = -1;
        for (auto it = begin(order); it != end(order); ++it)
            if (it != maxE) FOR(k,it->first)
                rst[(++i) % m] += it->second;
        return accumulate(begin(rst), end(rst), string());
    }
};

class SolutionV2 {///4ms 66.46% 8.1M 5.13%
    using vi = vector<int>;
    using pii = pair<int,int>;
public:
    string reorganizeString(string S) {
        int N = 26, n = S.size();
        if (n <= 1) return S;
        vi cnt(N, 0);
        for (char c : S) ++cnt[c - 'a'];
        vector<pii> order;
        FOR(i,N) if(cnt[i]) order.emplace_back(pii(cnt[i],i));
        auto maxE = max_element(begin(order), end(order));
        if (n + 1 < maxE->first * 2) return "";

        int no = order.size(), m = maxE->first;
        vector<string> rst(m, string(1, 'a' + maxE->second));
        int i = -1;
        for (auto it = begin(order); it != end(order); ++it)
            if (it != maxE) FOR(k,it->first)
                rst[(++i) % m] += 'a' + it->second;
        return accumulate(begin(rst), end(rst), string());
    }
};


class SolutionV1 {///4ms 66.46% 8.1M 5.13%
    using vi = vector<int>;
    using pii = pair<int,int>;
public:
    string reorganizeString(string S) {
        int N = 26, n = S.size();
        if (n <= 1) return S;
        vi cnt(N, 0);
        for (char c : S) ++cnt[c - 'a'];
        vector<pii> order;
        FOR(i,N) if(cnt[i]) order.emplace_back(pii(cnt[i],i));
        sort(rbegin(order), rend(order));
        if (n + 1 < order[0].first * 2) return "";

        int no = order.size(), m = order[0].first;
        vector<string> ans(m, string(1, 'a' + order[0].second));
        for (int i = -1, j = 1; j < no; ++j)
            FOR(k,order[j].first)
                ans[(++i) % m] += 'a' + order[j].second;
        return accumulate(begin(ans), end(ans), string());
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<string> xs{
        "aab",
        "aaab",
        ""
    };
    for (auto x : xs)
        print(x), print(Solution().reorganizeString(x)), print("===");
    return 0;
}
#endif
