#if defined(LocalLymphV)
#include "../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

示例 1:

输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:

输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
///栈
class Solution { ///4ms 95.03% 7.5M 10.69%
public:
    int longestValidParentheses(string s) {
        s = ")" + s;
        int n = s.size(), rst = 0;
        stack<int> st;
        st.push(0);
        ffor(i,1,n)
        {
            if (s[i] == '(') st.push(i);
            else if (s[st.top()] == '(')
            {
                st.pop();
                rst = max(rst, i - st.top());
            }
            else st.push(i);
        }
        return rst;
    }
};

///dp
class SolutionV2 { ///4ms 95.03% 7.5M 9.39%
public:
    int longestValidParentheses(string s) {
        s = ")" + s;
        int n = s.size(), rst = 0;
        vector<int> dp(n, 0);
        ffor(i,2,n)if (s[i] == ')')
        {
            if (s[i - 1] == '(')
                rst = max(rst, dp[i] = 2 + dp[i - 2]);
            else if (s[i - 1 - dp[i - 1]] == '(')
                rst = max(rst, dp[i] = 2 + dp[i - 1] + dp[i - 2 - dp[i - 1]]);
        }
        print(dp);
        return rst;
    }
};



///dp + 栈？
class SolutionV1 { /// 4ms 95.03% 7.9M 5.03%
public:
    int longestValidParentheses(string s) {
        s = ")" + s;
        int n = s.size(), rst = 0;
        stack<int> st;
        vector<int> dp(n, 0);
        FOR(i,n)
        {
            if (s[i] == ')')
            {
                if (!st.empty())
                {
                    int last = st.top(); st.pop();
                    rst = max(rst, dp[i] = i - last + 1 + dp[last - 1]);
                }
            }
            else st.push(i);
        }
        return rst;
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<string> xs{"(()", ")()())", "()(()","))))((()((", "()(())", "(()()"};
    for (auto x : xs)
        print(x), print(Solution().longestValidParentheses(x)), print("===");
    return 0;
}
#endif
