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
给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

示例 1:

给定 matrix =
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

原地旋转输入矩阵，使其变为:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
示例 2:

给定 matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
],

原地旋转输入矩阵，使其变为:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-image
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 63.49% 7.3M 29.37%
    void rotate (int & a, int & b, int & c, int & d)
    {
        int tmp = a;
        a = d;
        d = c;
        c = b;
        b = tmp;
    }

public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int l = 0, r = n - 1; l < r; ++l, --r) ffor(i,l,r)
            rotate(matrix[l][i], matrix[i][r],
                    matrix[r][n - 1 - i], matrix[n - 1 - i][l]);
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vector<vi>> xs{
        {  { 5, 1, 9,11},  { 2, 4, 8,10}, {13, 3, 6, 7},  {15,14,12,16}}
    };
    for (auto x : xs)
        print(x), Solution().rotate(x), print(x), print("===");
    return 0;
}
#endif
