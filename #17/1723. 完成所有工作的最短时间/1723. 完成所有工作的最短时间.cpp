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
给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。

请你将这些工作分配给 k 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。工人的 工作时间 是完成分配给他们的所有工作花费时间的总和。请你设计一套最佳的工作分配方案，使工人的 最大工作时间 得以 最小化 。

返回分配方案中尽可能 最小 的 最大工作时间 。

 

示例 1：

输入：jobs = [3,2,3], k = 3
输出：3
解释：给每位工人分配一项工作，最大工作时间是 3 。
示例 2：

输入：jobs = [1,2,4,7,8], k = 2
输出：11
解释：按下述方式分配工作：
1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
2 号工人：4、7（工作时间 = 4 + 7 = 11）
最大工作时间是 11 。
 

提示：

1 <= k <= jobs.length <= 12
1 <= jobs[i] <= 107

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 7.3M 60.71%
    using vi = vector<int>;
    bool check(int w, vi & jobs, vi & workers, int k, int i = 0)
    {
        if (i == jobs.size()) return 1;
        FOR(j,k)if (jobs[i] + workers[j] <= w)
        {
            workers[j] += jobs[i];
            if (check(w, jobs, workers, k, i + 1)) return 1;
            workers[j] -= jobs[i];
            if (!workers[j] || workers[j] + jobs[i] == w) break;
        }
        return 0;
    }
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        sort(rbegin(jobs), rend(jobs));

        int l = jobs[0], r = accumulate(begin(jobs), end(jobs), 0);
        while (l < r)
        {
            int m = l + (r - l) / 2;
            vi workers(k, 0);
            if (check(m, jobs, workers, k)) r = m;
            else l = m + 1;
        }
        return l;
    }
};

class SolutionV1 {///0ms 100.00 7.2M 78.85%
    using vi = vector<int>;
    bool check(int w, vi & jobs, vi & workers, int k, int i = 0)
    {
        if (i == jobs.size()) return 1;
        FOR(j,k)if (jobs[i] + workers[j] <= w)
        {
            workers[j] += jobs[i];
            if (check(w, jobs, workers, k, i + 1)) return 1;
            workers[j] -= jobs[i];
            if (!workers[j]) break;
        }
        return 0;
    }
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        sort(rbegin(jobs), rend(jobs));

        int l = jobs[0], r = accumulate(begin(jobs), end(jobs), 0);
        while (l < r)
        {
            int m = l + (r - l) / 2;
            vi workers(k, 0);
            if (check(m, jobs, workers, k)) r = m;
            else l = m + 1;
        }
        return l;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<vi,int>> xs{
        //{{6518448,8819833,7991995,7454298,2087579,380625,4031400,2905811,4901241,8480231,7750692,3544254},4}
        //{{254,256,256,254,251,256,254,253,255,251,251,255},10},
        {{5129437,1842905,2200851,597069,8618690,5823974,3199380,2416829,7138804,2445093,7207875,7133141},3}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().minimumTimeRequired(x,y)), print("===");
    return 0;
}
#endif
