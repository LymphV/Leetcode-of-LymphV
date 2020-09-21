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


#include <algorithm>
typedef vector<int>::iterator vit;
#define FOR(x,y) for (int x = 0; x < y; ++x)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int m = a.size(), n = b.size();
        int tot = m + n;
        if (tot & 1) return f(a.begin(), a.end(), b.begin(), b.end(), tot / 2);
        return (f(a.begin(), a.end(), b.begin(), b.end(), tot / 2)
            + f(a.begin(), a.end(), b.begin(), b.end(), tot / 2 - 1)) / 2.;
    }

    ///左边有k个数
    double f (vit ai, vit aj, vit bi, vit bj, int k)
    {
        int m = aj - ai, n = bj - bi;

        if (n < m) return f(bi,bj,ai,aj,k);

        if (!m) return bi[k];
        if (!k) return min(ai[0],bi[0]);
        if (k == 1)
        {
            if (ai[0] == bi[0]) return ai[0];
            if (ai[0] < bi[0])
                return m == 1 ? bi[0] : min(bi[0], ai[1]);
            return n == 1 ? ai[0] : min(ai[0], bi[1]);
        }

        if (m == 1)
            return f(bi,bj,k,ai[0]);


        int t = min(m - 1, k / 2);
        //print (k,t, ai[0], bi[0], m, n);

        if (ai[t] < bi[t])
            return f(ai + t, aj , bi, bj, k - t);
        return f(ai, aj, bi + t, bj, k - t);
    }

    double f(vit bi, vit bj, int k, int x)
    {
        int lb = lower_bound(bi,bj,x) - bi;
        if (k < lb) return *(bi + k);
        else if (k == lb) return x;
        else return *(bi + k - 1);
    }
};

int main ()
{
    //vector<int> a{1,3}, b{2};
    //vector<int> a{1,2}, b{3,4};
    vector<int> a{1}, b{2,3,4};
    print(Solution().findMedianSortedArrays(a,b));
    return 0;
}
