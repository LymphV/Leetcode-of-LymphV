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
����һ������ļ��ϣ��ҵ���Ҫ�Ƴ��������С������ʹʣ�����以���ص���

ע��:

������Ϊ������յ����Ǵ���������㡣
���� [1,2] �� [2,3] �ı߽��໥���Ӵ�������û���໥�ص���
ʾ�� 1:

����: [ [1,2], [2,3], [3,4], [1,3] ]

���: 1

����: �Ƴ� [1,3] ��ʣ�µ�����û���ص���
ʾ�� 2:

����: [ [1,2], [1,2], [1,2] ]

���: 2

����: ����Ҫ�Ƴ����� [1,2] ��ʹʣ�µ�����û���ص���
ʾ�� 3:

����: [ [1,2], [2,3] ]

���: 0

����: �㲻��Ҫ�Ƴ��κ����䣬��Ϊ�����Ѿ������ص����ˡ�

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/non-overlapping-intervals
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///40ms 54.08% 9.2M 88.87%
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (!n) return 0;
        sort(begin(intervals), end(intervals));
        int rst = 0;
        for (int i = 0, j = 1; j < n; i = j++)
        {
            for(; j < n && intervals[j][0] < intervals[i][1]; ++rst)
            {
                if (intervals[i][1] < intervals[j][1]) ++j;
                else i = j++;
            }
        }
        return rst;
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
