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
给你一个字符串 s ，请你根据下面的算法重新构造字符串：

从 s 中选出 最小 的字符，将它 接在 结果字符串的后面。
从 s 剩余字符中选出 最小 的字符，且该字符比上一个添加的字符大，将它 接在 结果字符串后面。
重复步骤 2 ，直到你没法从 s 中选择字符。
从 s 中选出 最大 的字符，将它 接在 结果字符串的后面。
从 s 剩余字符中选出 最大 的字符，且该字符比上一个添加的字符小，将它 接在 结果字符串后面。
重复步骤 5 ，直到你没法从 s 中选择字符。
重复步骤 1 到 6 ，直到 s 中所有字符都已经被选过。
在任何一步中，如果最小或者最大字符不止一个 ，你可以选择其中任意一个，并将其添加到结果字符串。

请你返回将 s 中字符重新排序后的 结果字符串 。

 

示例 1：

输入：s = "aaaabbbbcccc"
输出："abccbaabccba"
解释：第一轮的步骤 1，2，3 后，结果字符串为 result = "abc"
第一轮的步骤 4，5，6 后，结果字符串为 result = "abccba"
第一轮结束，现在 s = "aabbcc" ，我们再次回到步骤 1
第二轮的步骤 1，2，3 后，结果字符串为 result = "abccbaabc"
第二轮的步骤 4，5，6 后，结果字符串为 result = "abccbaabccba"
示例 2：

输入：s = "rat"
输出："art"
解释：单词 "rat" 在上述算法重排序以后变成 "art"
示例 3：

输入：s = "leetcode"
输出："cdelotee"
示例 4：

输入：s = "ggggggg"
输出："ggggggg"
示例 5：

输入：s = "spo"
输出："ops"
 

提示：

1 <= s.length <= 500
s 只包含小写英文字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/increasing-decreasing-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 97.00% 7.9M 25.65%
    using vi = vector<int>;
public:
    string sortString(string s) {
        int m = 26, n = 0;
        vi cnt(m);
        for(char c : s) if(++cnt[c - 'a'] == 1) ++n;
        string rst = "";
        auto l = begin(cnt), r = end(cnt);
        while(n)
        {
            if (n == 1)
            {
                auto it = max_element(l, r);
                char k = 'a' + (it - l);
                int v = *it;
                rst += string(v, k);
                break;
            }

            FOR(i,m)if (cnt[i])
            {
                if (!--cnt[i]) --n;
                rst += 'a' + i;
            }

            for (int i = m - 1; ~i; --i) if (cnt[i])
            {
                if(!--cnt[i]) --n;
                rst += 'a' + i;
            }
        }
        return rst;
    }
};

class SolutionV2 {///4ms 97.00% 7.8M 29.39%
    using vi = vector<int>;
public:
    string sortString(string s) {
        int m = 26;
        vi cnt(m);
        for(char c : s) ++cnt[c - 'a'];
        string rst = "";
        auto l = begin(cnt), r = end(cnt);
        for (int n = s.size(); n; )
        {
            /*if (n == 1)
            {
                auto it = max_element(l, r);
                char k = 'a' + (it - l);
                int v = *it;
                rst += string(v, k);
                break;
            }*/

            FOR(i,m)if (cnt[i]) --cnt[i], rst += 'a' + i, --n;

            for (int i = m - 1; ~i; --i) if (cnt[i]) --cnt[i], rst += 'a' + i, --n;
        }
        return rst;
    }
};

class SolutionV1 {///24ms 31.83% 8.6M 6.75%
public:
    string sortString(string s) {
        map<char,int> cnt;
        for(char c : s) ++cnt[c];
        string rst = "";
        while (!cnt.empty())
        {
            if (cnt.size() == 1)
            {
                auto & [k, v] = *begin(cnt);
                rst += string(v, k);
                break;
            }

            vector<char> cs;
            for (auto & [k, v] : cnt)
            {
                rst += k;
                if (!--v) cs.emplace_back(k);
            }
            for (char c : cs) cnt.erase(c);
            cs.clear();
            for (auto it = cnt.rbegin(); it != cnt.rend(); ++it)
            {
                auto & [k, v] = *it;
                rst += k;
                if (!--v) cs.emplace_back(k);
            }
            for (char c : cs) cnt.erase(c);
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<string> xs{
        "rat",
        "aaaabbbbcccc",
        "leetcode",
        "ggggggg",
        "spo",
        ""
    };
    for (auto x : xs)
        print(x), print(Solution().sortString(x)), print("===");
    return 0;
}
#endif
