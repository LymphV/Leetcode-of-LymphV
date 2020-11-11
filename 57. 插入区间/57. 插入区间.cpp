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
给出一个无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

 

示例 1：

输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]
示例 2：

输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
 

注意：输入类型已在 2019 年 4 月 15 日更改。请重置为默认代码定义以获取新的方法签名。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-interval
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///28ms 58.90% 17.2M 8.85%
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int a = newInterval[0], b = newInterval[1];
        int i = 0, n = intervals.size();
        if (!n) return {newInterval};
        vector<vector<int>> rst;
        for (; i < n; ++i)
        {
            if (intervals[i][1] < a) rst.emplace_back(intervals[i]);
            else break;
        }
        int left = i == n ? a  : min(intervals[i][0], a), right;

        for(;i < n && intervals[i][0] <= b; ++i);
        right = i ? max(b, intervals[i - 1][1]) : b;

        rst.emplace_back(vector<int>{left, right});

        for (; i < n; ++i)
            rst.emplace_back(intervals[i]);
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<vector<vi>, vi>> xs{
        {{},{1,2}},
        {{{1,5}},{6,8}},
        {{{1,5}},{2,3}}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().insert(x,y)), print("===");
    return 0;
}
#endif
