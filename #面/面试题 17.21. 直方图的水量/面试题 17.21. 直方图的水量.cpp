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
������ 17.21. ֱ��ͼ��ˮ��
����һ��ֱ��ͼ(Ҳ����״ͼ)���������˴�����ԴԴ���ϵص�ˮ�����ֱ��ͼ�ܴ����ˮ��?ֱ��ͼ�Ŀ��Ϊ 1��



������������ [0,1,0,2,1,0,1,3,2,1,2,1] ��ʾ��ֱ��ͼ������������£����Խ� 6 ����λ��ˮ����ɫ���ֱ�ʾˮ���� ��л Marcos ���״�ͼ��

ʾ��:

����: [0,1,0,2,1,0,1,3,2,1,2,1]
���: 6
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///8ms 61.71% 13.5M 74.19%
public:
    int trap(vector<int>& height) {
        int rst = 0, n = height.size();
        int maxL = 0, maxR = 0;
        FOR(i,n)
        {
            maxL = max(maxL, height[i]);
            maxR = max(maxR, height[n - 1 - i]);
            rst += maxL + maxR - height[i];
        }
        rst -= n * maxL;
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
