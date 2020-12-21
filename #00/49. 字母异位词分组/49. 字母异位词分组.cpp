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
给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
说明：

所有输入均为小写字母。
不考虑答案输出的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/group-anagrams
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///56ms 95.30% 20.6M 14.85%
    using vs = vector<string>;
    static const int N = 26;

    string count (string & s)
    {
        string rst(N, 0);
        for (char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vs> mp;
        for (string & x : strs) mp[count(x)].emplace_back(x);
        vector<vs> rst;
        for (auto & x : mp) rst.emplace_back(x.second);
        return rst;
    }
};
class SolutionV3 {///64ms 85.52% 20.5M 21.31%
    using vs = vector<string>;
    static const int N = 26;

    string count (string & s)
    {
        string rst(N, 0);
        for (char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vs> mp;
        for (string & x : strs) mp[count(x)].emplace_back(x);
        vector<vs> rst;
        for (auto & [k, v] : mp) rst.emplace_back(v);
        return rst;
    }
};

class SolutionV2 {///108ms 19.89% 22.8M 7.89%
    using vs = vector<string>;
    using vi = vector<int>;
    static const int N = 26;

    vi count (string & s)
    {
        vi rst(N);
        for (char c : s) ++rst[c - 'a'];
        return rst;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<vi, vs> mp;
        for (string & x : strs) mp[count(x)].emplace_back(x);
        vector<vs> rst;
        for (auto & [k, v] : mp) rst.emplace_back(v);
        return rst;
    }
};

class SolutionV1 {///76ms 62.74% 19.4M 51.54%
    using vs = vector<string>;
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vs> mp;
        for (string & x : strs)
        {
            string s = x;
            sort(begin(s), end(s));
            mp[s].emplace_back(x);
        }
        vector<vs> rst;
        for (auto & [k, v] : mp) rst.emplace_back(v);
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<string>> xs{
        {"eat", "tea", "tan", "ate", "nat", "bat"},
        {}
    };
    for (auto x : xs)
        print(x), print(Solution().groupAnagrams(x)), print("===");
    return 0;
}
#endif
