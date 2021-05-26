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
给你一个整数数组 nums​​​ 和一个整数 k​​​​​ 。区间 [left, right]（left <= right）的 异或结果 是对下标位于 left 和 right（包括 left 和 right ）之间所有元素进行 XOR 运算的结果：nums[left] XOR nums[left+1] XOR ... XOR nums[right] 。

返回数组中 要更改的最小元素数 ，以使所有长度为 k 的区间异或结果等于零。

 

示例 1：

输入：nums = [1,2,0,3,0], k = 1
输出：3
解释：将数组 [1,2,0,3,0] 修改为 [0,0,0,0,0]
示例 2：

输入：nums = [3,4,5,2,1,7,3,4,7], k = 3
输出：3
解释：将数组 [3,4,5,2,1,7,3,4,7] 修改为 [3,4,7,3,4,7,3,4,7]
示例 3：

输入：nums = [1,2,4,1,2,5,1,2,6], k = 3
输出：3
解释：将数组[1,2,4,1,2,5,1,2,6] 修改为 [1,2,3,1,2,3,1,2,3]
 

提示：

1 <= k <= nums.length <= 2000
​​​​​​0 <= nums[i] < 210

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/make-the-xor-of-all-segments-equal-to-zero
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///264ms 81.88% 19.6M 78.02%
    static const int N = 1024;
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[k][N], g = n;
        int tot = 0;
        unordered_map<int,int> cnt;
        for (int p = 0; p < n; p += k) ++cnt[nums[p]], ++tot;

        FOR(j,N)
            if (cnt.count(j)) dp[0][j] = tot - cnt[j];
            else dp[0][j] = tot;

        ffor(i,1,k)
        {
            g = n;
            FOR(j,N) g = min(g, dp[i - 1][j]);
            cnt.clear(), tot = 0;
            for (int p = i; p < n; p += k) ++cnt[nums[p]], ++tot;
            FOR(j,N)
            {
                int & t = dp[i][j];
                t = g + tot;
                for (auto [x, y] : cnt) t = min(t, dp[i - 1][x ^ j] + tot - y);
            }
        }
        return dp[k - 1][0];
    }
};

class SolutionV4 {///272ms 80.37% 19.7M 77.35%
    static const int N = 1024;
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[k][N], g = n;
        int tot = 0;
        unordered_map<int,int> cnt;
        for (int p = 0; p < n; p += k) ++cnt[nums[p]], ++tot;

        FOR(j,N)
            if (cnt.count(j)) dp[0][j] = tot - cnt[j];
            else dp[0][j] = tot;

        ffor(i,1,k)
        {
            g = n;
            FOR(j,N) g = min(g, dp[i - 1][j]);
            cnt.clear(), tot = 0;
            for (int p = i; p < n; p += k) ++cnt[nums[p]], ++tot;
            FOR(j,N)
            {
                int & t = dp[i][j];
                t = n;


                t = min(t, g + tot);
                for (auto [x, y] : cnt) t = min(t, dp[i - 1][x ^ j] + tot - y);
            }
        }
        return dp[k - 1][0];
    }
};

class SolutionV3 {///TLE
    static const int N = 1024;
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[k][N], g = n;
        int tot = 0;
        unordered_map<int,int> cnt;
        for (int p = 0; p < n; p += k) ++cnt[nums[p]], ++tot;

        FOR(j,N)
            if (cnt.count(j)) dp[0][j] = tot - cnt[j];
            else dp[0][j] = tot;

        ffor(i,1,k)
        {
            g = n;
            FOR(j,N) g = min(g, dp[i - 1][j]);
            FOR(j,N)
            {
                int & t = dp[i][j];

                cnt.clear(), tot = 0;
                for (int p = i; p < n; p += k) ++cnt[nums[p]], ++tot;

                t = min(t, g + tot);
                for (auto [x, y] : cnt) t = min(t, dp[i - 1][x ^ j] + tot - y);
            }
        }
        return dp[k - 1][0];
    }
};

class SolutionV2 {///TLE
    static const int N = 1024;
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[k][N];
        int tot = 0, cnt[N];
        MS(cnt,0);
        for (int p = 0; p < n; p += k) ++cnt[nums[p]], ++tot;

        FOR(j,N) dp[0][j] = tot - cnt[j];

        ffor(i,1,k)FOR(j,N)
        {
            int & t = dp[i][j];
            t = n;

            MS(cnt,0), tot = 0;
            for (int p = i; p < n; p += k) ++cnt[nums[p]], ++tot;

            FOR(m,N) t = min(t, dp[i - 1][m] + tot - cnt[m ^ j]);
        }
        return dp[k - 1][0];
    }
};

class SolutionV1 {///TLE
    static const int N = 1024;
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[k][N];
        FOR(j,N)
        {
            int & d = dp[0][j];
            d = 0;
            for (int p = 0; p < n; p += k) if (nums[p] != j) ++d;
        }

        ffor(i,1,k)FOR(j,N)
        {
            int & d = dp[i][j];
            d = n;
            FOR(m,N)
            {
                int t = m ^ j, cnt = 0;
                for (int p = i; p < n; p += k) if (nums[p] != t) ++cnt;
                d = min(d, cnt + dp[i - 1][m]);
            }
        }
        return dp[k - 1][0];
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        {{1,2,0,3,0},1}
        ,{{3,4,5,2,1,7,3,4,7},3}
        ,{{24,30,31,0,12,6,4,11,4,15,24,23,18,6,0,8,3,13,12,13,2,20,18,7,22,2,7,30,19,2,16,9,26,16,24,28,26,18,6,3,21,2,25,19,20,14,24,10},27}
        ,{{67,101,73,239,200,79,137,0,65,145,0,51,244,234,1,229,198,133,241,178,158,111,39,164,203,145,127,113,103,248,87,199,202,4,36,19,141,141,58,188,31,253,223,151,88,36,174,242,1,113,217,114,233,40,221,212,218,142,135,206,133,216,90,13,169,108,218,89,104,82,162,247,34,222,13,80,183,139,230,182,114,88,95,102,175,148,150,110,189,10,104,23,86,34,95,158,227,159,147,0,249,96,157,224,33,150,61,130,25,229,173,217,35,86,220,63,26,216,148,82,103,206,23,28,17,146,117,158,153,64,230,150,255,208,168,137,7,219,56,7,199,95,61,78,20,122,227,189,109,86,181,24,4,160,244,122,79,57,63,173,49,44,14,145,129,38,163,240,38,252,190,239,180,18,211,23,57,177,206,140,160,171,63,120,191,3,126,139,213,88,39,67,122,67,210,157,119,92,85,152,195,151,167,199,128,132,221,23,11,225,231,159,133,21,152,52,49,46,76,112,146,10,77},75}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().minChanges(x, y)), print("===");
    return 0;
}
#endif
