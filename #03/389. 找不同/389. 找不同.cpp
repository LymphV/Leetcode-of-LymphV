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
给定两个字符串 s 和 t，它们只包含小写字母。

字符串 t 由字符串 s 随机重排，然后在随机位置添加一个字母。

请找出在 t 中被添加的字母。

 

示例 1：

输入：s = "abcd", t = "abcde"
输出："e"
解释：'e' 是那个被添加的字母。
示例 2：

输入：s = "", t = "y"
输出："y"
示例 3：

输入：s = "a", t = "aa"
输出："a"
示例 4：

输入：s = "ae", t = "aea"
输出："a"
 

提示：

0 <= s.length <= 1000
t.length == s.length + 1
s 和 t 只包含小写字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-the-difference
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 6.9M 27.23%
public:
    char findTheDifference(string s, string t) {
        char rst = 0;
        for (char c : s) rst ^= c;
        for (char c : t) rst ^= c;
        return rst;
    }
};

class SolutionV2 {///16ms 12.97% 6.7M 56.04%
public:
    char findTheDifference(string s, string t) {
        sort(begin(s), end(s));
        sort(begin(t), end(t));
        for (int i = 0, n = s.size(); i < n; ++i)
            if (s[i] != t[i]) return t[i];
        return t.back();
    }
};


class SolutionV1 {///4ms 73.81% 7M 10.94%
public:
    char findTheDifference(string s, string t) {
        vector<int> cnt(26, 0);
        for (char c : s) ++cnt[c - 'a'];
        for (char c : t)
            if (--cnt[c - 'a'] < 0)
                return c;
        return 0;
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
