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
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。

整数除法仅保留整数部分。

 

示例 1：

输入：s = "3+2*2"
输出：7
示例 2：

输入：s = " 3/2 "
输出：1
示例 3：

输入：s = " 3+5 / 2 "
输出：5
 

提示：

1 <= s.length <= 3 * 105
s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
s 表示一个 有效表达式
表达式中的所有整数都是非负整数，且在范围 [0, 231 - 1] 内
题目数据保证答案是一个 32-bit 整数

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/basic-calculator-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 93.11 8.7M 45.53%
    vector<int> st;
    char last;

    int get (string & s, int & i)
    {
        int n = s.size();
        while (i < n && s[i] == ' ') ++i;
        if (i == n) return -1;
        int rst = ('0' <= s[i] && s[i] <= '9' ? 1 : 2);
        if (rst == 2)
        {
            last = s[i];
            ++i;
        }
        else
        {
            int v = 0;
            for (; i < n && '0' <= s[i] && s[i] <= '9'; ++i) v = v * 10 + (s[i] - '0');
            switch (last)
            {
            case '+': st.emplace_back(v);break;
            case '-': st.emplace_back(-v);break;
            case '*': st.back() *= v;break;
            case '/': st.back() /= v;break;
            }
        }
        return rst;
    }
public:
    int calculate(string s) {
        last = '+';
        for (int i = 0, n = s.size(); i < n;) get(s, i);
        return accumulate(begin(st), end(st), 0);
    }
};

class SolutionV1 {///24ms 27.51% 7.8M 88.36%
    stack<int> s1;
    stack<char> s2;

    int mp (char c)
    {
        switch (c)
        {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        }
        return 0;
    }

    int cal (int a, int b, char c)
    {
        switch (c)
        {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        }
        return 0;
    }

    void cal (char c)
    {
        while (!s2.empty() && (!c || mp(c) <= mp(s2.top())))
        {
            int b = s1.top();s1.pop();
            int a = s1.top();s1.pop();
            char c = s2.top();s2.pop();
            s1.push(cal(a,b,c));
        }
        if (c) s2.push(c);
    }

    int get (string & s, int & i)
    {
        int n = s.size();
        while (i < n && s[i] == ' ') ++i;
        if (i == n) return -1;
        int rst = ('0' <= s[i] && s[i] <= '9' ? 1 : 2);
        if (rst == 2)
        {
            cal(s[i]);
            ++i;
        }
        else
        {
            int v = 0;
            for (; i < n && '0' <= s[i] && s[i] <= '9'; ++i) v = v * 10 + (s[i] - '0');
            s1.push(v);
        }
        return rst;
    }
public:
    int calculate(string s) {
        int n = s.size();
        for (int i = 0; i < n;) get(s, i);
        cal(0);
        return s1.top();
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<string> xs{
        /*"1",
        "1+2",
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 ",*/
        "1*2-3/4+5*6-7*8+9/10"
    };
    for (auto & x : xs)
        print(x), print(Solution().calculate(x)), print("===");
    return 0;
}
#endif
