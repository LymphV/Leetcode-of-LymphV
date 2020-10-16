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
ʵ�ֻ�ȡ��һ�����еĺ������㷨��Ҫ���������������������г��ֵ�������һ����������С�

�����������һ����������У��������������г���С�����У����������У���

����ԭ���޸ģ�ֻ����ʹ�ö��ⳣ���ռ䡣

������һЩ���ӣ�����λ������У�����Ӧ���λ���Ҳ��С�
1,2,3 �� 1,3,2
3,2,1 �� 1,2,3
1,1,5 �� 1,5,1

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/next-permutation
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///16ms 26.17% 12.2M 12.3%
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n - 1;
        for (; 0 < k && nums[k] <= nums[k - 1]; --k);
        --k;
        for (int i = k + 1, j = n - 1; i < j; ++i, --j)
            swap(nums[i],nums[j]);
        if (~k)
        {
            int m = upper_bound(begin(nums) + k + 1, end(nums), nums[k]) - begin(nums);
            swap(nums[m], nums[k]);
        }
    }
};


///�⺯��
class SolutionV1 {///8ms 66.00% 12.2M 5.23%
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(begin(nums),end(nums));
    }
};


#if defined(LocalLymphV)
int main()
{
    /*vi a {1,2,3,4};
    do
    {
        print(a);
    }while (next_permutation(begin(a), end(a)));*/

    vector<vi> xs{
        {1,3,2,4},
        {3,2,1},
        {1},
        {1,2},
        {1,5,1,1},
        {1,2,3}
    };
    for (auto x : xs)
        print(x), Solution().nextPermutation(x), print(x), print("===");
    return 0;
}
#endif
