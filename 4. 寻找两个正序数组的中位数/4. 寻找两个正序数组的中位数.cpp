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

#define FOR(x,y) for (int x = 0; x < y; ++x)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int m = a.size(), n = b.size();
        int i, j, K =(m + n) / 2;
        i = j = 0;
        double rst = 0;

        int t;
        FOR(k,K+1)
        {
            if (i == a.size()) t = b[j++];
            else if (j == b.size() || a[i] < b[j]) t = a[i++];
            else t = b[j++];

            if (k == K - 1 && !((m + n) & 1)) rst = t;
        }
        if ((m + n) & 1) return t;
        return (rst + t) / 2;
    }
};

int main ()
{
    vector<int> a{1,3}, b{2};
    print(Solution().findMedianSortedArrays(a,b));
    return 0;
}
