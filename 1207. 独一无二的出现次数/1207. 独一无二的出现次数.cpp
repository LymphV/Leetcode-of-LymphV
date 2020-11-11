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
给你一个整数数组 arr，请你帮忙统计数组中每个数的出现次数。

如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。

 

示例 1：

输入：arr = [1,2,2,1,1,3]
输出：true
解释：在该数组中，1 出现了 3 次，2 出现了 2 次，3 只出现了 1 次。没有两个数的出现次数相同。
示例 2：

输入：arr = [1,2]
输出：false
示例 3：

输入：arr = [-3,0,1,-3,1,1,1,-3,10,0]
输出：true
 

提示：

1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-number-of-occurrences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///8ms 47.90% 8.5M 25.11%
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> cnt;
        for (int & x : arr) ++cnt[x];
        unordered_set<int> rst;
        for (const auto & [k, v] : cnt)
        {
            if (rst.count(v)) return 0;
            rst.insert(v);
        }
        return 1;
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,2}
    };
    for (auto x : xs)
        print(x), print(Solution().uniqueOccurrences(x)), print("===");
    return 0;
}
#endif
