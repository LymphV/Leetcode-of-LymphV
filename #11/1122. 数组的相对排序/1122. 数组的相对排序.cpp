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
给你两个数组，arr1 和 arr2，

arr2 中的元素各不相同
arr2 中的每个元素都出现在 arr1 中
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

 

示例：

输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]
 

提示：

arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2 中的元素 arr2[i] 各不相同
arr2 中的每个元素 arr2[i] 都出现在 arr1 中

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/relative-sort-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///4ms 88.86% 7.9M 16.97%
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int m = arr1.size(), n = arr2.size(), N = 1010;
        vector<int> mp(N, 0);
        for (int x : arr1) ++mp[x];
        vector<int> rst;
        for (int x : arr2)
            for (int & y = mp[x]; y; --y)
                rst.emplace_back(x);
        FOR(x,N) for (int & y = mp[x]; y; --y)
            rst.emplace_back(x);
        return rst;
    }
};


class SolutionV3 {///4ms 88.86% 8M 8.45%
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int m = arr1.size(), n = arr2.size();

        map<int,int> mp;
        for (int x : arr1) ++mp[x];
        vector<int> rst;
        for (int x : arr2)
        {
            for (int & y = mp[x]; y; --y)
                rst.emplace_back(x);
            mp.erase(x);
        }
        for (auto [x, y] : mp)
            while(y--) rst.emplace_back(x);
        return rst;
    }
};

class SolutionV2 {///8ms 56.78% 8M 9.48%
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int n = arr2.size();
        unordered_map<int,int> mp;
        FOR(i,n) mp[arr2[i]] = i - n;
        sort(begin(arr1), end(arr1), [&](int x, int y)
        {
            return mp[x] < mp[y] || mp[x] == mp[y] && x < y;
        });
        return arr1;
    }
};


class SolutionV1 {///20ms 5.02% 8.1M 7.73%
    using pii = pair<int,int>;
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int n = arr2.size();
        unordered_map<int,int> mp;
        FOR(i,n) mp[arr2[i]] = i;
        sort(begin(arr1), end(arr1), [&](int x, int y)
        {
            auto f = [&](int a)
            {
                return mp.count(a) ? pii(mp[a], a) : pii(n, a);
            };
            return f(x) < f(y);
        });
        return arr1;
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
