/**
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。

请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

 

示例 1:

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include<LymphV>
#include <cassert>


typedef vector<int>::iterator vit;
#define FOR(x,y) for (int x = 0; x < y; ++x)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b)
    {
        int m = a.size(), n = b.size();
        if (m <= n) return findMedianSortedArrays(a.begin(), a.end(), b.begin(), b.end());
        return findMedianSortedArrays(b.begin(), b.end(), a.begin(), a.end());
    }
    double findMedianSortedArrays (vit ai, vit aj, vit bi, vit bj)
    {
        while (aj - ai >= 3)
        {
            vit ma = ai + (aj - ai) / 2;
            vit mb = bi + (bj - bi) / 2;
            int drop = aj - ma - 1;
            if (*ma < *mb) ai += drop, bj -= drop;
            else aj -= drop, bi += drop;
        }

        return findMedian(ai, aj, bi, bj);
    }


    double findMedian (vit ai, vit aj, vit bi, vit bj)
    {
        int m = aj - ai, n = bj - bi;

        if (!m)
        {
            if (n & 1) return *(bi+n/2);
            return (*(bi+n/2) + *(bi+(n-1)/2)) / 2.;
        }

        if (m == 1)
        {
            if (n & 1) return (f(bi,bj,(n+1)/2,*ai) + f(bi,bj,n/2,*ai)) / 2.;
            return f(bi,bj,n/2,*ai);
        }

        if (n & 1) return f(bi,bj,n/2+1,ai[0],*(ai+1));
        return (f(bi,bj,n/2+1,*ai,*(ai+1)) + f(bi,bj,n/2,*ai,*(ai+1))) / 2.;

/*
        int i, j, K =(m + n) / 2;
        double rst = 0;

        int t;
        FOR(k,K+1)
        {
            if (ai == aj) t = *(bi++);
            else if (bi == bj || *ai < *bi) t = *(ai++);
            else t = *(bi++);

            if (k == K - 1 && !((m + n) & 1)) rst = t;
        }
        if ((m + n) & 1) return t;
        return (rst + t) / 2;*/
    }

    double f(vit bi, vit bj, int k, int x)
    {
        int lb = lower_bound(bi,bj,x) - bi;
        if (k < lb) return *(bi + k);
        else if (k == lb) return x;
        else return *(bi + k - 1);
    }

    double f(vit bi, vit bj, int k, int x, int y)
    {
        int lbx = lower_bound(bi,bj,x) - bi;
        int lby = lower_bound(bi,bj,y) - bi;

       // print (k, x, lbx, y, lby);
        if (k < lbx) return *(bi + k);
        else if (k == lbx) return x;
        else if (lbx < k && k <= lby)return *(bi + k - 1);
        else if (k == lby + 1) return y;
        else return *(bi + k - 2);
    }

};

int main ()
{
    //vector<int> a{}, b{1};
    //vector<int> a{1,2}, b{3,4};
    vector<int> a{1,2}, b{1,2,3};
    print(Solution().findMedianSortedArrays(a,b));
    return 0;
}
