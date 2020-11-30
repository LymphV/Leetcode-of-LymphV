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
����һ������ nums����дһ������������ 0 �ƶ��������ĩβ��ͬʱ���ַ���Ԫ�ص����˳��

ʾ��:

����: [0,1,0,3,12]
���: [1,3,12,0,0]
˵��:

������ԭ�����ϲ��������ܿ�����������顣
�������ٲ���������

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/move-zeroes
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 91.02% 9.2M 13.08%
public:
    void moveZeroes(vector<int>& nums) {
        for (auto i = begin(nums), j = begin(nums); j != end(nums); ++j)
            if (*j) swap(*(i++), *j);
    }
};


class SolutionV1 {///8ms 91.02% 9.1M 21.60%
public:
    void moveZeroes(vector<int>& nums) {
        for (auto i = begin(nums), j = begin(nums); i != end(nums); ++i)
        {
            if (j == end(nums)) *i = 0;
            else
            {
                while (j != end(nums) && !*j) ++j;
                if (j != end(nums)) *i = *(j++);
                else *i = 0;
            }
        }
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {0,1,0},
        {0}
    };
    for (auto x : xs)
        print(x), (Solution().moveZeroes(x)), print(x), print("===");
    return 0;
}
#endif
