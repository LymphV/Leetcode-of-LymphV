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
给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。

然而，两个 相同种类 的任务之间必须有长度为整数 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的 最短时间 。

 

示例 1：

输入：tasks = ["A","A","A","B","B","B"], n = 2
输出：8
解释：A -> B -> (待命) -> A -> B -> (待命) -> A -> B
     在本示例中，两个相同类型任务之间必须间隔长度为 n = 2 的冷却时间，而执行一个任务只需要一个单位时间，所以中间出现了（待命）状态。
示例 2：

输入：tasks = ["A","A","A","B","B","B"], n = 0
输出：6
解释：在这种情况下，任何大小为 6 的排列都可以满足要求，因为 n = 0
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
诸如此类
示例 3：

输入：tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
输出：16
解释：一种可能的解决方案是：
     A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> (待命) -> (待命) -> A -> (待命) -> (待命) -> A
 

提示：

1 <= task.length <= 104
tasks[i] 是大写英文字母
n 的取值范围为 [0, 100]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/task-scheduler
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///116ms 97.95% 34.1M 31.77%
    using vi = vector<int>;
public:
    int leastInterval(vector<char>& tasks, int n) {
        int t = tasks.size(), maxCnt = 0, m = 0;
        if (!n) return t;
        vi cnt(26);
        for (char x : tasks) maxCnt = max(maxCnt, ++cnt[x - 'A']);
        for (int x : cnt) if (x == maxCnt) ++m;
        if ((t - maxCnt * m) <= (maxCnt - 1) * (n - m + 1)) return (maxCnt - 1) * (n - m + 1) + maxCnt * m;
        return t;
    }
};

class SolutionV1 {///128ms 86.04% 34.1M 23.13%
    using vi = vector<int>;
public:
    int leastInterval(vector<char>& tasks, int n) {
        int t = tasks.size();
        if (!n) return t;
        vi cnt(26);
        for (char x : tasks) ++cnt[x - 'A'];
        int maxCnt = *max_element(begin(cnt), end(cnt));
        int m = 0;
        for (int x : cnt) if (x == maxCnt) ++m;
        if ((t - maxCnt * m) <= (maxCnt - 1) * (n - m + 1)) return (maxCnt - 1) * (n - m + 1) + maxCnt * m;
        return t;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<vector<char>,int>> xs{
        {{'A','A','A','B','B','B'},2},
        {{'A','A','A','A','A','A','B','C','D','E','F','G'},2},
        {{'A','A','B','B','C','C','D','D'},2},
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().leastInterval(x,y)), print("===");
    return 0;
}
#endif
