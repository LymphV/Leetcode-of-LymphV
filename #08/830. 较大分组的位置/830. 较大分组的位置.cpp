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
在一个由小写字母构成的字符串 s 中，包含由一些连续的相同字符所构成的分组。

例如，在字符串 s = "abbxxxxzyy" 中，就含有 "a", "bb", "xxxx", "z" 和 "yy" 这样的一些分组。

分组可以用区间 [start, end] 表示，其中 start 和 end 分别表示该分组的起始和终止位置的下标。上例中的 "xxxx" 分组用区间表示为 [3,6] 。

我们称所有包含大于或等于三个连续字符的分组为 较大分组 。

找到每一个 较大分组 的区间，按起始位置下标递增顺序排序后，返回结果。

 

示例 1：

输入：s = "abbxxxxzzy"
输出：[[3,6]]
解释："xxxx" 是一个起始于 3 且终止于 6 的较大分组。
示例 2：

输入：s = "abc"
输出：[]
解释："a","b" 和 "c" 均不是符合要求的较大分组。
示例 3：

输入：s = "abcdddeeeeaabbbcd"
输出：[[3,5],[6,9],[12,14]]
解释：较大分组为 "ddd", "eeee" 和 "bbb"
示例 4：

输入：s = "aba"
输出：[]
 
提示：

1 <= s.length <= 1000
s 仅含小写英文字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/positions-of-large-groups
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 48.24% 7.6M 61.50%
    using vi = vector<int>;
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vi> rst;
        int last = -1, n = s.size();
        char c = 0;
        FOR(i,n) if (s[i] != c)
        {
            if (3 <= i - last) rst.emplace_back(vi{last, i - 1});
            c = s[last = i];
        }
        if (3 <= n - last) rst.emplace_back(vi{last, n - 1});
        return rst;
    }
};

class Solution {///8ms 48.24% 7.6M 45.74%
    using vi = vector<int>;
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vi> rst;
        int cnt = 0, n = s.size();
        char c = 0;
        FOR(i,n)
        {
            if (s[i] != c)
            {
                if (3 <= cnt) rst.emplace_back(vi{i - cnt, i - 1});
                cnt = 1;
                c = s[i];
            }
            else ++cnt;
        }
        if (3 <= cnt) rst.emplace_back(vi{n - cnt, n - 1});
        return rst;
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
