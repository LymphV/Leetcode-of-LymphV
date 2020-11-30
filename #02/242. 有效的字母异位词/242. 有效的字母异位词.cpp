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
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

示例 1:

输入: s = "anagram", t = "nagaram"
输出: true
示例 2:

输入: s = "rat", t = "car"
输出: false
说明:
你可以假设字符串只包含小写字母。

进阶:
如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-anagram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 98.93% 7.8M 5.08%
    vector<int> count(string s)
    {
        vector<int> rst(26);
        for(char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return 0;
        auto && cnt = count(s);
        for (char c : t)
            if (--cnt[c - 'a'] < 0)
                return 0;
        return all_of(begin(cnt), end(cnt), [](int x){return x == 0;});
    }
};


class SolutionV5 {///0ms 100.00% 7.8M 5.08%
    vector<int> count(string s)
    {
        vector<int> rst(26);
        for(char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return 0;
        return count(s) == count(t);
    }
};

class SolutionV4 {///80ms 19.76% 7.5M 25.74%
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return 0;
        sort(begin(s), end(s));
        sort(begin(t), end(t));
        return s == t;
    }
};

class SolutionV3 {///76ms 25.42% 7.4M 47.65%
public:
    bool isAnagram(string s, string t) {
        sort(begin(s), end(s));
        sort(begin(t), end(t));
        return s == t;
    }
};

class SolutionV2 {///8ms 85.13% 7.8M 5.08%
    vector<int> count(string s)
    {
        vector<int> rst(26);
        for(char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    bool isAnagram(string s, string t) {
        return count(s) == count(t);
    }
};

class SolutionV1 {///20ms 51.30% 8M 5.08%
    unordered_map<char,int> count(string s)
    {
        unordered_map<char,int> rst;
        for(char c : s) ++rst[c];
        return rst;
    }
public:
    bool isAnagram(string s, string t) {
        return count(s) == count(t);
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
