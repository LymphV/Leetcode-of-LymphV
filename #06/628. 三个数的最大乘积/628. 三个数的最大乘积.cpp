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

*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///44ms 95.85% 27M 79.38%
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 3) return nums[0] * nums[1] * nums[2];
        if (n == 4)
        {
            sort(begin(nums), end(nums));
            return max(nums[0] * nums[1] * nums[n - 1], nums[n - 1] * nums[n - 2] * nums[n - 3]);
        }

        partial_sort(begin(nums), begin(nums) + 2, end(nums));
        partial_sort(begin(nums) + 2, begin(nums) + 5, end(nums), greater<int>());

        return max(nums[0] * nums[1] * nums[2], nums[2] * nums[3] * nums[4]);
    }
};

class SolutionV4 {///56ms 90.60% 27.2M 72.24%
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        priority_queue<int> q1, q2;
        sort(begin(nums), begin(nums) + 3);
        q1.push(nums[0]), q1.push(nums[1]);
        q2.push(-nums[0]), q2.push(-nums[1]), q2.push(-nums[2]);
        ffor(i,3,n)
        {
            q1.push(nums[i]), q2.push(-nums[i]);
            q1.pop(), q2.pop();
        }
        int b = q1.top(); q1.pop();
        int a = q1.top();
        int c = -q2.top(); q2.pop();
        int d = -q2.top(); q2.pop();
        int e = -q2.top();

        return max(a * b * e, c * d * e);
    }
};

class SolutionV3 {///36ms 98.82% 27.1M 72.24%
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        priority_queue<int> q1, q2;
        sort(begin(nums), begin(nums) + 3);
        q1.push(nums[0]), q1.push(nums[1]);
        q2.push(-nums[0]), q2.push(-nums[1]), q2.push(-nums[2]);
        ffor(i,3,n)
        {
            if (nums[i] < q1.top())
            {
                q1.push(nums[i]);
                q1.pop();
            }
            if (-q2.top() < nums[i])
            {
                q2.push(-nums[i]);
                q2.pop();
            }
        }
        int b = q1.top(); q1.pop();
        int a = q1.top();
        int c = -q2.top(); q2.pop();
        int d = -q2.top(); q2.pop();
        int e = -q2.top();

        return max(a * b * e, c * d * e);
    }
};

class SolutionV2 {///36ms 98.82% 27.1M 72.91%
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        int a, b, c, d, e;
        sort(begin(nums), begin(nums) + 3);
        a = c = nums[0];
        b = d = nums[1];
        e = nums[2];
        ffor(i,3,n)
        {
            if (e < nums[i])
            {
                c = d;
                d = e;
                e = nums[i];
            }
            else if (d < nums[i])
            {
                c = d;
                d = nums[i];
            }
            else if (c < nums[i]) c = nums[i];
            if (nums[i] < a)
            {
                b = a;
                a = nums[i];
            }
            else if (nums[i] < b) b = nums[i];
        }
        return max(a * b * e, c * d * e);
    }
};

class SolutionV1 {///60ms 89.09% 27M 79.76%
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));
        return max(nums[0] * nums[1] * nums[n - 1], nums[n - 1] * nums[n - 2] * nums[n - 3]);
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {1,1,2,2},
        {1,2,3,4}
    };
    for (auto & x : xs)
        print(x), print(Solution().maximumProduct(x)), print("===");
    return 0;
}
#endif
