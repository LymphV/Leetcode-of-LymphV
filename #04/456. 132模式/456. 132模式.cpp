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
给定一个整数序列：a1, a2, ..., an，一个132模式的子序列 ai, aj, ak 被定义为：当 i < j < k 时，ai < ak < aj。设计一个算法，当给定有 n 个数字的序列时，验证这个序列中是否含有132模式的子序列。

注意：n 的值小于15000。

示例1:

输入: [1, 2, 3, 4]

输出: False

解释: 序列中不存在132模式的子序列。
示例 2:

输入: [3, 1, 4, 2]

输出: True

解释: 序列中有 1 个132模式的子序列： [1, 4, 2].
示例 3:

输入: [-1, 3, 2, 0]

输出: True

解释: 序列中有 3 个132模式的的子序列: [-1, 3, 2], [-1, 3, 0] 和 [-1, 2, 0].

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/132-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///12ms 89.69% 13.3M 75.99%
    using vi = vector<int>;
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        int maxV = minVs[n - 3];
        stack<int> monostack;
        monostack.push(nums.back());
        for (int i = n - 2; i; --i)
        {
            while (!monostack.empty() && monostack.top() < nums[i])
            {
                maxV = max(maxV, monostack.top());
                monostack.pop();
            }
            if (monostack.empty() || monostack.top() != nums[i])monostack.push(nums[i]);
            if (minVs[i - 1] < maxV) return 1;
        }
        return 0;
    }
};

class SolutionV8 {///16ms 69.77% 13.1M 91.67%
    using vi = vector<int>;
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        int maxV = minVs[n - 3];
        vi monostack{nums.back()};
        for (int i = n - 2; i; --i)
        {
            while (!monostack.empty() && monostack.back() <= nums[i])
            {
                if (monostack.back() != nums[i]) maxV = max(maxV, monostack.back());
                monostack.pop_back();
            }
            monostack.emplace_back(nums[i]);
            if (minVs[i - 1] < maxV) return 1;
        }
        return 0;
    }
};

class SolutionV7 {///384ms 14.13% 13M 95.48%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return 0;
        int minV, maxV;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        maxV = minV = nums.back();
        for (int i = n - 2; i; --i)
        {
            minV = min(minV, nums[i]);
            maxV = max(maxV, nums[i]);

            if (nums[i] <= minVs[i - 1] || nums[i] <= minV || maxV <= minVs[i - 1]) continue;

            for (int j = i + 1; j < n; ++j)
                if (minVs[i - 1] < nums[j] && nums[j] < nums[i])
                    return 1;
        }
        return 0;
    }
};

class SolutionV6 {///100ms 17.37% 13M 95.34%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return 0;
        int minV = min(nums[0], nums[1]);
        int maxV = max(nums[0], nums[1]);
        int rst = 0;
        ffor(i,2,n)
        {
            if (minV < nums[i] && nums[i] < maxV) rst = 1;
            minV = min(minV, nums[i]);
            maxV = max(maxV, nums[i]);
        }
        if (!rst) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        maxV = minV = nums.back();
        for (int i = n - 2; i; --i)
        {
            minV = min(minV, nums[i]);
            maxV = max(maxV, nums[i]);

            if (nums[i] <= minVs[i - 1] || nums[i] <= minV || maxV <= minVs[i - 1]) continue;

            for (int j = i + 1; j < n; ++j)
                if (minVs[i - 1] < nums[j] && nums[j] < nums[i])
                    return 1;
        }
        return 0;
    }
};

class SolutionV5 {///496ms 11.02% 12.9M 98.16%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return 0;
        int minV = min(nums[0], nums[1]);
        int maxV = max(nums[0], nums[1]);
        int rst = 0;
        ffor(i,2,n)
        {
            if (minV < nums[i] && nums[i] < maxV) rst = 1;
            minV = min(minV, nums[i]);
            maxV = max(maxV, nums[i]);
        }
        if (!rst) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        for (int i = n - 2; i; --i)
        {
            int x = nums[i];
            int j = i + 1;
            for(;j < n && nums[j] < x;++j)
                nums[j - 1] = nums[j];
            if (j == i + 1) continue;
            nums[j - 1] = x;
            if (minVs[i - 1] < nums[j - 2]) return 1;
        }
        return 0;
    }
};

class SolutionV4 {///1044ms 5.93 13M 94.21%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        for (int i = n - 2; i; --i)
        {
            int x = nums[i];
            int j = i + 1;
            for(;j < n && nums[j] < x;++j)
                nums[j - 1] = nums[j];
            if (j == i + 1) continue;
            nums[j - 1] = x;
            if (minVs[i - 1] < nums[j - 2]) return 1;
        }
        return 0;
    }
};

class SolutionV3 {///28ms 33.33% 14.8M 5.09%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        int minVs[n];
        minVs[0] = nums[0];
        ffor(i,1,n) minVs[i] = min(minVs[i - 1], nums[i]);

        set<int> ns{nums.back()};
        for (int i = n - 2; i; --i)
        {
            ns.insert(nums[i]);
            if (nums[i] <= minVs[i - 1]) continue;
            auto it = ns.find(nums[i]);
            if (it == begin(ns)) continue;
            --it;
            if (minVs[i - 1] < *it) return 1;
        }
        return 0;
    }
};

class SolutionV2 {///532ms 10.88% 12.9M 97.88%
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        int minV = min(nums[0], nums[1]);
        int maxV = max(nums[0], nums[1]);
        int rst = 0;
        ffor(i,2,n)
        {
            if (minV < nums[i] && nums[i] < maxV) rst = 1;
            minV = min(minV, nums[i]);
            maxV = max(maxV, nums[i]);
        }
        if (!rst) return 0;
        FOR(i,n-2)
        {
            int minValue = nums[i];
            for (int j = n - 1; i < j - 1; --j)
            {
                if (nums[i] < nums[j])
                {
                    if (minValue == nums[i]) minValue = nums[j];
                    else minValue = min(minValue, nums[j]);
                }
                if (nums[i] < minValue && minValue < nums[j - 1]) return 1;
            }
        }
        return 0;
    }
};


class SolutionV1 {///TLE
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        FOR(i,n-2)
        {
            int minValue = nums[i];
            for (int j = n - 1; i < j - 1; --j)
            {
                if (nums[i] < nums[j])
                {
                    if (minValue == nums[i]) minValue = nums[j];
                    else minValue = min(minValue, nums[j]);
                }
                if (nums[i] < minValue && minValue < nums[j - 1]) return 1;
            }
        }
        return 0;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {3,5,0,3,4},
        {1,0,1,-4,-3},
        {3, 1, 4, 2}
    };
    for (auto & x : xs)
        print(x), print(Solution().find132pattern(x)), print("===");
    return 0;
}
#endif
