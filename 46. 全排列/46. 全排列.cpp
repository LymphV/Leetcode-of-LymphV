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
����һ�� û���ظ� ���ֵ����У����������п��ܵ�ȫ���С�

ʾ��:

����: [1,2,3]
���:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/permutations
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 89.21% 7.9M 23.96%
    bool nextPermutation(vector<int>& nums) {
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
        return k != -1;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<vector<int>> rst{nums};
        while (nextPermutation(nums)) rst.emplace_back(nums);
        return rst;
    }
};


///std
class SolutionV1 {///0ms 100.00% 7.8M 29.39%
public:
    vector<vector<int>> permute(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<vector<int>> rst{nums};
        while (next_permutation(begin(nums), end(nums))) rst.emplace_back(nums);
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
