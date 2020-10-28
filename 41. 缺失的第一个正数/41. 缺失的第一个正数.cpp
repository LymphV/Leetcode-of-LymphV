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
给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

 

示例 1:

输入: [1,2,0]
输出: 3
示例 2:

输入: [3,4,-1,1]
输出: 2
示例 3:

输入: [7,8,9,11,12]
输出: 1
 

提示：

你的算法的时间复杂度应为O(n)，并且只能使用常数级别的额外空间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/first-missing-positive
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///swap
class Solution {///0ms 100.00% 10M 6.43%
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        FOR(i,n)
        {
            for (int j = i; 0 < nums[j] && nums[j] <= n && nums[nums[j] - 1] != nums[j];)
            {
                int k = nums[j] - 1;
                swap(nums[j], nums[k]);
                print(nums, j, k);
            }
            if (n < nums[i]) nums[i] = -1;
            if (0 < nums[i] && nums[i] <= n && nums[nums[i] - 1] == nums[i] && nums[i] - 1 != i) nums[i] = -1;
        }print(nums);
        FOR(i,n) if (nums[i] <= 0) return i + 1;
        return n + 1;
    }
};

///原地set
class SolutionV4 {///8ms 29.69% 9.9M 10.03%
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int & x : nums) if (x <= 0) x = n + 1;
        for (int x : nums)
        {
            int y = abs(x) - 1;
            if (0 <= y && y < n)
                nums[y] = -abs(nums[y]);
        }
        FOR(i,n) if (0 < nums[i]) return i + 1;
        return n + 1;
    }
};


///bitset
class SolutionV3 {///8ms 29.69% 9.9M 9.26%
public:
    int firstMissingPositive(vector<int>& nums) {
        bitset<300> cnt;
        for (int x : nums)
        {
            if (x < 1 || 300 < x) continue;
            cnt.set(x - 1);
        }
        FOR(i,300) if (!cnt[i]) return i + 1;

        return 301;
    }
};

///定长vector<bool>
class SolutionV2 {///12ms 29.69% 10M 5.28%
public:
    int firstMissingPositive(vector<int>& nums) {
        vector<bool> cnt(300);
        for (int x : nums)
        {
            if (x < 1 || 300 < x) continue;
            cnt[x - 1] = true;
        }
        int n = cnt.size();
        FOR(i,n) if (!cnt[i]) return i + 1;

        return 301;
    }
};


///变长vector<bool>
class SolutionV1 {///184ms 29.69% 295.4M 5.11%
public:
    int firstMissingPositive(vector<int>& nums) {
        vector<bool> cnt;
        for (int x : nums)
        {
            if (x < 1) continue;
            if (cnt.size() < x )
                cnt.resize(x);
            cnt[x - 1] = true;
        }
        int n = cnt.size();print(cnt);
        FOR(i,n) if (!cnt[i]) return i + 1;

        return n + 1;
    }
};



#if defined(LocalLymphV)
int main()
{

    vector<vi> xs{
        {3,4,-1,1},
        {1,2,0}
    };
    for (auto x : xs)
        print(x), print(Solution().firstMissingPositive(x)), print("===");
    return 0;
}
#endif
