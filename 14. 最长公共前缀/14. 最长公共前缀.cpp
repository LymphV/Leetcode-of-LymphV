#include <LymphV>

/***
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-common-prefix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#define FOR(x,y) for (int x = 0; x < y; ++x)
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        return accumulate(strs.begin(),
                            strs.end(),
                            strs[0],
                            [](string a, string b)
                            {
                                if (a.size() < b.size())
                                    return string (begin(a), mismatch(begin(a),end(a),begin(b)).first);
                                return string(begin(b), mismatch(begin(b),end(b),begin(a)).first);
                            });
    }
};


class SolutionV1 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        return accumulate(strs.begin(),
                          strs.end(),
                          strs[0],
                          [](string a, string b)
                          {
                              int l = min(a.size(),b.size());
                              FOR(i,l) if (a[i] != b[i]) return string(a.begin(),a.begin()+i);
                              return a.size() < b.size() ? a : b;
                          });
    }
};


int main ()
{
    vector<vector<string>> xs{
        {"flower","flow","flight"},
        {"dog","racecar","car"}
    };
    for (auto x : xs)
        print(x, Solution().longestCommonPrefix(x));
}
