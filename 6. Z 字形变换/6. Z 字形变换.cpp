/**
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zigzag-conversion
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#ifdef LocalLymphV
#include <LymphV>
#endif // LocalLymphV

#include <vector>
#define FOR(x,y) for (int x = 0; x < y; ++x)
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        string rst = "";
        int cycle = 2 * numRows - 2;
        FOR(i,numRows)
        {
            vector<int> step{i * 2, cycle - i * 2};
            int flag = step[0] ? 0 : 1;
            for(int j = i; j < s.size(); j += step[flag])
            {
                rst += s[j];
                flag ^= 1;
                if (step[flag] == 0) flag ^= 1;
            }
        }
        return rst;
    }
};

int main ()
{
    string s1 = "LEETCODEISHIRING";
    string s2 = "LEETCODEISHIRING";
    print(Solution().convert(s1,2));

    print(Solution().convert(s2,4));
    print(Solution().convert("A",1));

    return 0;
}
