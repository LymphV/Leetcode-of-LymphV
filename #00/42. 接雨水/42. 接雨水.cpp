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
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

 

示例 1：



输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
示例 2：

输入：height = [4,2,0,3,2,5]
输出：9
 

提示：

n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trapping-rain-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///双指针
class Solution {///16ms 14.15% 14.4M 8.00%
    using vi = vector<int>;
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;
        int left = 0, right = n - 1, leftMax = 0, rightMax = 0, rst = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                if (height[left] < leftMax) rst += leftMax - height[left];
                else leftMax = height[left];
                ++left;
            }
            else
            {
                if (height[right] < rightMax) rst += rightMax - height[right];
                else rightMax = height[right];
                --right;
            }
        }
        return rst;
    }
};

///左右最大值
class SolutionV4 {///16ms 14.15% 14.4M 8.91%
    using vi = vector<int>;
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;
        vi rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; 0 <= i; --i)
            rightMax[i] = max(rightMax[i + 1], height[i]);
        int leftMax = height[0], rst = 0;
        ffor(i,1,n)
        {
            leftMax = max(leftMax, height[i]);
            rst += min(leftMax, rightMax[i]) - height[i];
        }
        return rst;
    }
};


///双指针 维护值的最左和最右
class SolutionV3 {///28ms 6.24% 15.6M 5.13%
    using itr = vector<int>::iterator;
    using pii = pair<int,int>;

    map<int,pii,greater<int>> pos;
    vector<int> tot;

    int solve (int h, int first, int last)
    {
        if (first - last == 1) return 0;
        return h * (last - first - 1) - tot[last] + tot[first + 1];
    }
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;

        tot = vector<int>(n + 1);
        partial_sum(begin(height), end(height), begin(tot) + 1);

        FOR(i,n)
        {
            if (pos.count(height[i]))
                pos[height[i]].second = i;
            else pos[height[i]] = pii(i,i);
        }

        if (pos.empty()) return 0;
        auto [left, right] = begin(pos)->second;
        int rst = solve(begin(pos)->first, left, right);
        for (auto it = begin(pos); it != end(pos) && (1 < left || right < n - 2); ++it)
        {
            auto h = it->first;
            auto [pl, pr] = it->second;
            if (pl < left)
            {
                rst += solve(h, pl, left);
                left = pl;
            }
            if (right < pr)
            {
                rst += solve(h, right, pr);
                right = pr;
            }
        }
        return rst;
    }
};

///双指针 全排序
class SolutionV2 {///36ms 5.60% 15M 5.13%
    using itr = vector<int>::iterator;
    using pii = pair<int,int>;

    vector<pii> pos;
    vector<int> tot;

    int solve (int h, int first, int last)
    {
        return h * (last - first - 1) - tot[last] + tot[first + 1];
    }
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;

        tot = vector<int>(n + 1);
        partial_sum(begin(height), end(height), begin(tot) + 1);

        FOR(i,n) pos.emplace_back(pii(height[i], i));

        if (pos.empty()) return 0;
        sort(begin(pos), end(pos), greater<pii>());
        int left, right;
        left = right = pos[0].second;

        int rst = 0, m = pos.size();
        for (int i = 1; i < m && (1 < left || right < n - 2); ++i)
        {
            auto [h, p] = pos[i];
            if (p < left)
            {
                rst += solve(h, p, left);
                left = p;
            }
            else if (right < p)
            {
                rst += solve(h, right, p);
                right = p;
            }
        }
        return rst;
    }
};

///暴力max_element
class SolutionV1 {///16ms 14.15% 14.7M 5.13%
    using itr = vector<int>::iterator;

    //map<int, vector<int>> pos;
    vector<int> tot;

    int solveLeft (itr start, int first, int last)
    {   //print("left",first,last);
        if (last - first < 3) return 0;
        auto maxEle = max_element(start + first, start + last - 1);
        int mid = maxEle - start;
        return *maxEle * (last - mid - 2) - tot[last - 1] + tot[mid + 1] + solveLeft(start, first, mid + 1);
    }
    int solveRight (itr start, int first, int last)
    {   //print("right", first,last);
        if (last - first < 3) return 0;
        auto maxEle = max_element(start + first + 1, start + last);
        int mid = maxEle - start;
        return *maxEle * (mid - first - 1) - tot[mid] + tot[first + 1] + solveRight(start, mid, last);
    }
public:
    int trap(vector<int>& height) {
        height.insert(height.begin(), 0);
        height.emplace_back(0);
        int n = height.size();
        /*
        ffor(i,1,n-1)
            if (height[i - 1] <= height[i] && height[i + 1] <= height[i])
                pos[height[i]].insert(i);*/

        tot = vector<int>(n + 1);
        partial_sum(begin(height), end(height), begin(tot) + 1);

        auto maxEle = max_element(begin(height), end(height));
        int mid = maxEle - begin(height);
        return solveLeft(begin(height), 0,  mid + 1)
              + solveRight(begin(height), mid, n);
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<vi> xs{
        {5,4,1,2},
        {4,2,0,3,2,5},
        {0,1,0,2,1,0,1,3,2,1,2,1}
    };

    for (auto x : xs)
        print(x), print(Solution().trap(x)), print("===");
    return 0;
}
#endif
