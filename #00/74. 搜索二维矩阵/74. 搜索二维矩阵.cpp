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
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。
 

示例 1：


输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
示例 2：


输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-a-2d-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///4ms 87.61% 9.2M 77.74%
    using vi = vector<int>;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto it = lower_bound(begin(matrix), end(matrix), vi{target + 1});
        if (it == begin(matrix)) return 0;
        --it;
        return binary_search(it->begin(), it->end(), target);
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
