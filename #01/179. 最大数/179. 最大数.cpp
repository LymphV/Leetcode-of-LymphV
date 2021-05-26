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
给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。

注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。

 

示例 1：

输入：nums = [10,2]
输出："210"
示例 2：

输入：nums = [3,30,34,5,9]
输出："9534330"
示例 3：

输入：nums = [1]
输出："1"
示例 4：

输入：nums = [10]
输出："10"
 

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///
    using ll = long long;
public:
    string largestNumber(vector<int>& nums) {///0ms 100.00% 10.7M 94.35%
        sort(begin(nums), end(nums), [](int a, int b) -> bool
        {
            ll x = a, y = b, z = a, w = b;
            do b /= 10, x *= 10; while (b);
            do a /= 10, y *= 10; while (a);
            return y + z < x + w;
        });
        if (nums[0] == 0) return "0";
        string rst = "";
        for (int x : nums) rst += to_string(x);
        return rst;
    }
};

class SolutionV3 {///12ms 71.50% 10.8M 65.69%
public:
    string largestNumber(vector<int>& nums) {
        sort(begin(nums), end(nums), [](int a, int b) -> bool
        {
            string x = to_string(a), y = to_string(b);
            return y + x < x + y;
        });
        if (nums[0] == 0) return "0";
        string rst = "";
        for (int x : nums) rst += to_string(x);
        return rst;
    }
};

class SolutionV2 {///4ms 99.03% 12.7M 5.03%
    using vs = vector<string>;
public:
    string largestNumber(vector<int>& nums) {
        vs ns;
        for (int x : nums) ns.emplace_back(to_string(x));
        sort(begin(ns), end(ns), [](string & a, string & b) -> bool
        {
            int n = a.size(), m = b.size();
            for (int i = 0; i < n + m; ++i)
            {
                char x = i < n ? a[i] : b[i - n], y = i < m ? b[i] : a[i - m];
                if (x != y) return x < y;
            }
            return 0;
        });
        if (ns.back() == "0") return "0";
        return accumulate(rbegin(ns), rend(ns), string());
    }
};

class SolutionV1 {///4ms 99.03% 12.8M 5.03%
    using vs = vector<string>;
public:
    string largestNumber(vector<int>& nums) {
        vs ns;
        for (int x : nums) ns.emplace_back(to_string(x));
        sort(begin(ns), end(ns), [](string & a, string & b){return a + b < b + a;});
        if (ns.back() == "0") return "0";
        return accumulate(rbegin(ns), rend(ns), string());
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {3,30,34,5,9},
        {0,9,8,7,6,5,4,3,2,1},
        {1,2,3,4,5,6,7,8,9,0}
    };
    for (auto & x : xs)
        print(x), print(Solution().largestNumber(x)), print("===");
    return 0;
}
#endif
