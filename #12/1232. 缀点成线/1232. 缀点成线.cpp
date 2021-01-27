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
在一个 XY 坐标系中有一些点，我们用数组 coordinates 来分别记录它们的坐标，其中 coordinates[i] = [x, y] 表示横坐标为 x、纵坐标为 y 的点。

请你来判断，这些点是否在该坐标系中属于同一条直线上，是则返回 true，否则请返回 false。

 

示例 1：



输入：coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
输出：true
示例 2：



输入：coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
输出：false
 

提示：

2 <= coordinates.length <= 1000
coordinates[i].length == 2
-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
coordinates 中不含重复的点

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-it-is-a-straight-line
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///8ms 99.57% 9.8M 99.34%
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        if (n < 3) return 1;
        int x0 = coordinates[0][0], y0 = coordinates[0][1];
        int a = coordinates[1][0] - x0, b = coordinates[1][1] - y0;
        ffor(i,2,n)
            if (a * (coordinates[i][1] - y0) != b * (coordinates[i][0] - x0))
                return 0;
        return 1;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {{1,2},{2,3},{3,4},{4,5},{5,6},{6,7}}
    };
    for (auto & x : xs)
        print(x), print(Solution().checkStraightLine(x)), print("===");
    return 0;
}
#endif
