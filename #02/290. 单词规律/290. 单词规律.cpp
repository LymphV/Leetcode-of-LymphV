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
给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false
示例 3:

输入: pattern = "aaaa", str = "dog cat cat dog"
输出: false
示例 4:

输入: pattern = "abba", str = "dog dog dog dog"
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///0ms 100.00% 6.8M 14.18%
    static const int N = 26;
public:
    bool wordPattern(string pattern, string s) {
        vector<string> p2s(N);
        unordered_set<string> s2p;
        int i = 0, n = s.size();
        for (char c : pattern)
        {
            if (n <= i) return 0;
            int j = i;
            while (j < n && s[j] != ' ') ++j;
            string ss = string(begin(s) + i, begin(s) + j);
            string & st = p2s[c - 'a'];

            if (st.empty() && s2p.find(ss) == end(s2p)) st = ss, s2p.insert(ss);
            else if (st.empty() || s2p.find(ss) == end(s2p) || st != ss) return 0;
            i = j + 1;
        }
        return n <= i;
    }
};


class SolutionV1 {///4ms 41.29% 6.6M 39.74%
    static const int N = 26;
public:
    bool wordPattern(string pattern, string s) {
        vector<string> p2s(N);
        unordered_map<string, char> s2p;
        int i = 0, n = s.size();
        for (char c : pattern)
        {
            if (n <= i) return 0;
            int j = i;
            while (j < n && s[j] != ' ') ++j;
            string ss = string(begin(s) + i, begin(s) + j);
            if (p2s[c - 'a'].empty() && s2p.find(ss) == end(s2p)) p2s[c - 'a'] = ss, s2p[ss] = c;
            else if (p2s[c - 'a'].empty() || s2p.find(ss) == end(s2p) || p2s[c - 'a'] != ss) return 0;
            i = j + 1;
        }
        return n <= i;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        {"abba", "dog cat cat dog"},
        {"abba", "dog cat cat fish"},
        {"aaaa", "dog cat cat dog"},
        {"abba", "dog dog dog dog"}
    };
    for (auto & [x,y] : xs)
        print(x,y), print(Solution().wordPattern(x,y)), print("===");
    return 0;
}
#endif
