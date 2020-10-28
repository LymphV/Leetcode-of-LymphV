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
给定一个正整数 n（1 ≤ n ≤ 30），输出外观数列的第 n 项。

注意：整数序列中的每一项将表示为一个字符串。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
第一项是数字 1

描述前一项，这个数是 1 即 “一个 1 ”，记作 11

描述前一项，这个数是 11 即 “两个 1 ” ，记作 21

描述前一项，这个数是 21 即 “一个 2 一个 1 ” ，记作 1211

描述前一项，这个数是 1211 即 “一个 1 一个 2 两个 1 ” ，记作 111221

 

示例 1:

输入: 1
输出: "1"
解释：这是一个基本样例。
示例 2:

输入: 4
输出: "1211"
解释：当 n = 3 时，序列是 "21"，其中我们有 "2" 和 "1" 两组，"2" 可以读作 "12"，也就是出现频次 = 1 而 值 = 2；类似 "1" 可以读作 "11"。所以答案是 "12" 和 "11" 组合在一起，也就是 "1211"。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-and-say
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///骗时间
class Solution {///4ms 87.50% 6.9M 21.17%
    static vector<string> rst;
public:
    Solution()
    {
        if (rst.size()) return;
        rst = vector<string>(31, "");
        rst[1] = "1";
        ffor(i,1,31)
        {
            string & s1 = rst[i - 1];
            string & s2 = rst[i];
            int n = s1.size();
            int cnt = 0;
            FOR(i,n)
            {
                ++cnt;
                if (i == n - 1 || s1[i] != s1[i + 1])
                {
                    s2 += '0' + cnt;
                    s2 += s1[i];
                    cnt = 0;
                }
            }
        }
    }

    string countAndSay(int n) {
        print(rst);
        return rst[n];
    }
}a;
vector<string> Solution::rst;

class SolutionV1 {///148ms 6.82% 9M 15.81%
    vector<string> rst;
    template <typename T>
	inline string repr (const T & t)
	{
		stringstream ss;
		ss << t;
		return ss.str();
	}
public:
    SolutionV1():rst(31, "")
    {
        rst[1] = "1";
        ffor(i,1,31)
        {
            string & s1 = rst[i - 1];
            string & s2 = rst[i];
            int n = s1.size();
            int cnt = 0;
            FOR(i,n)
            {
                ++cnt;
                if (i == n - 1 || s1[i] != s1[i + 1])
                {
                    s2 += repr(cnt) + s1[i];
                    cnt = 0;
                }
            }
        }
    }

    string countAndSay(int n) {
        print(rst);
        return rst[n];
    }
};




#if defined(LocalLymphV)
int main()
{
    vector<int> xs{20};
    for (auto x : xs)
        print(x), print(Solution().countAndSay(x)), print("===");
    return 0;
}
#endif
