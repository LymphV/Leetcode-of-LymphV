#include <LymphV>
/**
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例：

输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/generate-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///8ms 58.06% 7.1M 98.78%
    using tsii = tuple<string, int, int>;
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> rst;
        string s = "";

        stack<tsii> stk;///string, cnt, stck
        stk.push(tsii("",0,0));

        while(!stk.empty())
        {
            auto [s, cnt, stck] = stk.top(); stk.pop();
            if (s.size() == n * 2) rst.push_back(s);
            else
            {
                if (cnt < n) stk.push(tsii(s + '(', cnt + 1, stck - 1));
                if (stck < 0) stk.push(tsii(s + ')', cnt, stck + 1));
            }
        }
        return rst;
    }
};

class SolutionV1 {///TLE
    vector<string> rst;
public:
    vector<string> generateParenthesis(int n, string s = "", int cnt = 0, int stk = 0) {
        if (s.size() == n * 2) rst.push_back(s);
        else
        {
            if (cnt < n) generateParenthesis(n, s + '(', cnt + 1, stk - 1);
            if (stk < 0) generateParenthesis(n, s + ')', cnt, stk + 1);
        }
        return rst;
    }
};

int main()
{
    vector<int> xs{3};
    for (auto x : xs)
        print(x, Solution().generateParenthesis(x));
    return 0;
}
