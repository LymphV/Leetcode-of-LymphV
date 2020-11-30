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
给定一个非负整数数组 A， A 中一半整数是奇数，一半整数是偶数。

对数组进行排序，以便当 A[i] 为奇数时，i 也是奇数；当 A[i] 为偶数时， i 也是偶数。

你可以返回任何满足上述条件的数组作为答案。

 

示例：

输入：[4,2,5,7]
输出：[4,5,2,7]
解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。
 

提示：

2 <= A.length <= 20000
A.length % 2 == 0
0 <= A[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-array-by-parity-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///36ms 97.91% 20.5M 30.79%
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        for (int i = 0, j = 1, n = A.size(); i < n; i += 2)
        {
            if (A[i] & 1)
            {
                while (A[j] & 1) j += 2;
                swap(A[i], A[j]);
            }
        }
        return A;
    }
};


class SolutionV2 {///68ms 7.98% 20.5M 29.26%
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int n = A.size();
        int now[2] = {0, 1};
        FOR(i,n)
        {
            while ((A[i] & 1) != (i & 1))
            {
                int j = A[i] & 1;
                while ((A[now[j]] & 1) == (now[j] & 1))
                    now[j] += 2;
                swap(A[i], A[now[j]]);
            }
        }
        return A;
    }
};

class SolutionV1 {///35.02% 20.3M 39.18%
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int n = A.size();
        int now[2] = {0, 1};
        FOR(i,n)
        {
            while ((A[i] & 1) != (i & 1))
            {
                swap(A[i], A[now[A[i] & 1]]);
                now[A[i] & 1] += 2;
            }
        }
        return A;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{

        {4,2,5,7}
    };
    for (auto x : xs)
        print(x), print(Solution().sortArrayByParityII(x)), print("===");
    return 0;
}
#endif
