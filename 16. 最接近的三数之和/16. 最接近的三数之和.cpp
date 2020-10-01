#include <LymphV>
/**
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，
使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

 

示例：

输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
 

提示：

3 <= nums.length <= 10^3
-10^3 <= nums[i] <= 10^3
-10^4 <= target <= 10^4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///12ms 9.9M O(n^2)
    int rst;
    int gap;
    int target;
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(begin(nums),end(nums));

        int n = nums.size();
        rst = nums[0] + nums[1] + nums[2];
        gap = abs(rst - target);
        this->target = target;
        FOR(i,n-2) for (int j = i + 1, k = n - 1; j < k;)
        {
            int now = nums[i] + nums[j] + nums[k];
            int gp = abs(now-target);
            if (gp <= gap)
                gap = gp, rst = now;

            if(!gap) return rst;
            if (now < target) ++j;
            else --k;
        }
        return rst;
    }
};

class SolutionV3 {///20ms 10M O(n^2)
    int rst;
    int gap;
    int target;
public:
    int update (vector<int> & nums, int i, int j, int k)
    {
        int gp = abs(nums[i]+nums[j]+nums[k]-target);
        if (gp <= gap)
            gap = gp, rst = nums[i] + nums[j] + nums[k];
        return gap;
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(begin(nums),end(nums));

        int n = nums.size();
        rst = nums[0] + nums[1] + nums[2];
        gap = abs(rst - target);
        this->target = target;
        FOR(i,n-2) for (int j = i + 1, k = n - 1; j < k; ++j)
        {
            int obj = target - nums[i] - nums[j];
            for (; j < k && obj < nums[k]; --k);
            if (j == k)
            {
                if (!update(nums,i,j,j+1)) return rst;
                break;
            }
            if (!update(nums,i,j,k)) return rst;
            if (k < n - 1) if(!update(nums,i,j,k+1)) return rst;
        }
        return rst;
    }
};

class SolutionV2 {///36ms 9.9M O(n^2)
    int rst;
    int gap;
    int target;
public:
    void update (vector<int> & nums, int i, int j, int k)
    {
        int gp = abs(nums[i]+nums[j]+nums[k]-target);
        if (gp <= gap)
            gap = gp, rst = nums[i] + nums[j] + nums[k];
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(begin(nums),end(nums));

        int n = nums.size();
        gap = abs(nums[0] + nums[1] + nums[2] - target);
        this->target = target;
        FOR(i,n-2) for (int j = i + 1, k = n - 1; j < k; ++j)
        {
            int obj = target - nums[i] - nums[j];
            for (; j < k && obj < nums[k]; --k);
            if (j == k)
            {
                update(nums,i,j,j+1);
                break;
            }
            update(nums,i,j,k);
            if (k < n - 1) update(nums,i,j,k+1);
        }
        return rst;
    }
};


class SolutionV1 {///836ms 9.9M 纯暴力O(n^3)
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        int rst;
        int gap = abs(nums[0] + nums[1] + nums[2] - target);
        FOR(i,n)ffor(j,i+1,n)ffor(k,j+1,n)
        {
            int gp = abs(nums[i]+nums[j]+nums[k]-target);
            if (gp <= gap)
                gap = gp, rst = nums[i] + nums[j] + nums[k];
        }
        return rst;
    }
};



int main()
{
    vector<pair<vector<int>,int>> xs{
        {{-1,2,1,-4},1},
        {{1,1,-1,-1,3},-1}
    };
    for (auto x : xs)
        print(x, Solution().threeSumClosest(x.first, x.second));
    return 0;
}
