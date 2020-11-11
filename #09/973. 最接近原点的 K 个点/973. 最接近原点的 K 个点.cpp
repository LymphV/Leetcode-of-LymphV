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
我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点 (0, 0) 最近的点。

（这里，平面上两点之间的距离是欧几里德距离。）

你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。

 

示例 1：

输入：points = [[1,3],[-2,2]], K = 1
输出：[[-2,2]]
解释：
(1, 3) 和原点之间的距离为 sqrt(10)，
(-2, 2) 和原点之间的距离为 sqrt(8)，
由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。
示例 2：

输入：points = [[3,3],[5,-1],[-2,4]], K = 2
输出：[[3,3],[-2,4]]
（答案 [[-2,4],[3,3]] 也会被接受。）
 

提示：

1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/k-closest-points-to-origin
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

///分治
class Solution {///248ms 94.16% 38.6M 74.73%
    using vi = vector<int>;
    using itr = vector<vi>::iterator;
    vector<vi> rst;

    template <class T>
    T median (T a, T b, T c, function<bool(T, T)> f)
    {
        if (f(a,b))
        {
            if (f(b,c)) return b;
            if (f(a,c)) return c;
            return a;
        }
        if (f(a,c)) return a;
        if (f(b,c)) return c;
        return b;
    }

    function<bool(const vi&,const vi&)> gt;
    function<bool(itr,itr)> gt2;

    void solve (itr left, itr right, int k)
    {
        if (!k) return;
        if (right - left < 2) return;
        if (right - left == 2)
        {
            if (!gt(*left,*(right-1))) swap(*left, *(right-1));
            return;
        }
        if (k == 1)
        {
            auto me = min_element(left, right, gt);
            swap(*left, *me);
            return;
        }
        auto med = median((left + (right - left) / 2),(right - 1),left,gt2);
        swap(*med, *left);
        auto mid = __unguarded_partition(left + 1, right, left, gt2);


        if (mid - left <= k) solve(mid, right, k - (mid - left));
        else solve(left, mid, k);
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        gt = [](const vi & a, const vi & b)
        {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        };
        gt2 = [&](itr a, itr b){return gt(*a,*b);};
        solve(begin(points), end(points), K);
        return vector<vi>(begin(points), begin(points) + K);
    }
};


///部分排序without 排序
class SolutionV5 {///352ms 76.73% 38.5M 76.02%
    using vi = vector<int>;
    using itr = vector<vi>::iterator;

    struct Cmp
    {
        bool operator()(const vi & a, const vi & b)
        {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        }
        bool operator()(const itr & a, const itr & b){return (*this)(*a, *b);}
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto first = begin(points), mid = begin(points) + K, last = end(points);
        __heap_select(first, mid, last, Cmp());
        return vector<vi>(first, mid);
    }
};


///部分排序
class SolutionV4 {///516ms 31.74% 38.5M 75.72%
    using vi = vector<int>;
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        partial_sort(begin(points), begin(points) + K, end(points), [](const vi & a, const vi & b)
             {
                 return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
             });
        return vector<vi>(begin(points), begin(points) + K);
    }
};


///分治
class SolutionV3 {///352ms 76.73% 38.6M 74.04%
    using vi = vector<int>;
    using itr = vector<vi>::iterator;
    vector<vi> rst;

    template <class T>
    T median (T a, T b, T c, function<bool(T, T)> f)
    {
        if (f(a,b))
        {
            if (f(b,c)) return b;
            if (f(a,c)) return c;
            return a;
        }
        if (f(a,c)) return a;
        if (f(b,c)) return c;
        return b;
    }

    function<bool(const vi&,const vi&)> gt;
    function<bool(itr,itr)> gt2;

    void solve (itr left, itr right, int k)
    {
        if (!k) return;
        if (right - left < 2) return;
        if (right - left == 2)
        {
            if (!gt(*left,*(right-1))) swap(*left, *(right-1));
            return;
        }
        if (k == 1)
        {
            auto me = min_element(left, right, gt);
            swap(*left, *me);
            return;
        }
        auto med = median((left + (right - left) / 2),(right - 1),left,gt2);
        swap(*med, *left);
        auto mid = __unguarded_partition(left + 1, right, left, gt2);


        if (mid - left <= k)
        {
            sort(left, mid, gt);
            solve(mid, right, k - (mid - left));
        }
        else solve(left, mid, k);
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        gt = [](const vi & a, const vi & b)
        {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        };
        gt2 = [&](itr a, itr b){return gt(*a,*b);};
        solve(begin(points), end(points), K);
        return vector<vi>(begin(points), begin(points) + K);
    }
};

///排序
class SolutionV2 {///360ms 74.68% 38.4M 77.70%
    using vi = vector<int>;
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(begin(points), end(points), [](const vi & a, const vi & b)
             {
                 return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
             });
        return vector<vi>(begin(points), begin(points) + K);
    }
};


///排序
class SolutionV1 {///1868ms 5.26% 187.4M 5.06%
    using vi = vector<int>;
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(begin(points), end(points), [](vi a, vi b)
             {
                 return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
             });
        return vector<vi>(begin(points), begin(points) + K);
    }
};



#if defined(LocalLymphV)
int main()
{
    vector<pair<vector<vi>,int>> xs{
        {{{1,3},{-2,2}},1},
        {
            {{-173,399},{62,-213},{71,282},{-45,851},{710,982},{493,985},{-529,-946},{-83,78},{624,-785},{877,-351},{500,-376},{-601,-305},{-23,-79},{-82,906},{-143,500},{-249,-260},{10,706},{-904,-632},{-402,458},{303,-970},{93,-552},{-362,-743},{705,986},{900,-524},{-680,-204},{-726,890},{-138,742},{-76,714},{813,474},{443,23},{-422,117},{768,214},{863,562},{728,-204},{778,147},{-56,-751},{240,454},{-106,-701},{-897,-770},{572,433},{-658,97},{-301,-466},{902,-371},{-38,-662},{-872,191},{659,294},{852,965},{-37,665},{541,-920},{-537,704}},
            20
        },
        {{{3,3},{5,-1},{-2,4}},2}
    };
    for (auto [x, y] : xs)
        print(x, y), print(Solution().kClosest(x,y)), print("===");
    return 0;
}
#endif
