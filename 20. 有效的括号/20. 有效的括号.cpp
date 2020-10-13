#include <LymphV>
/**
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。

示例 1:

输入: "()"
输出: true
示例 2:

输入: "()[]{}"
输出: true
示例 3:

输入: "(]"
输出: false
示例 4:

输入: "([)]"
输出: false
示例 5:

输入: "{[]}"
输出: true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 48.76% 6.3M 60.44%
    int f (char c)
    {
        switch (c)
        {
        case '[': return -1;
        case '(': return -2;
        case '{': return -3;
        case ']': return 1;
        case ')': return 2;
        case '}': return 3;
        }
        return 2020;
    }

public:
    bool isValid(string s) {
        int n = s.size();
        if (!n) return 1;

        stack<int> st;
        FOR(i,n)
        {
            if (st.empty() || st.top() > 0 || st.top() + f(s[i])) st.push(f(s[i]));
            else st.pop();
        }
        return st.empty();
    }
};

int main()
{
    vector<string> xs{"()","()[]{}","(]","([)]","{[]}"};
    ///1 1 0 0 1
    for (auto x : xs)
        print(x, Solution().isValid(x));
    return 0;
}
