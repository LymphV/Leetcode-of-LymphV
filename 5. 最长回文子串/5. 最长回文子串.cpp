/**
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include<algorithm>
#define FOR(x,y) for (int x = 0; x < y; ++x)
#define Ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {
public:
    string longestPalindrome(string s) {
        int l = s.size();
        if (!l) return "";
        int i = 0, j = 1;
        int rst = 1;
        FOR(c,l)
        {
            int W = min(c + 1, l - c);
            Ffor(w,1,W)
            {
                int ii = c - w, jj = c + w + 1;
                if (s[ii] != s[jj - 1]) break;
                if (rst < jj - ii)
                {
                    rst = jj - ii;
                    i = ii, j = jj;
                }
            }
        }
        Ffor(c,1,l)
        {
            int W = min(c + 1, l - c + 1);
            Ffor(w,1,W)
            {
                int ii = c - w, jj = c + w;
                if (s[ii] != s[jj - 1]) break;
                if (rst < jj - ii)
                {
                    rst = jj - ii;
                    i = ii, j = jj;
                }
            }
        }
        return string(s.begin() + i, s.begin() + j);
    }
};

