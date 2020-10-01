#include <LymphV>

/**
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。

 



图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

 

示例：

输入：[1,8,6,2,5,4,8,3,7]
输出：49

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define FOR(x,y) for (int x = 0; x < y; ++x)
using pii = pair<int,int>;



class Solution
{
public:
    int maxArea(vector<int>& h)
    {
        int rst = 0;
        for (int l = 0, r = h.size() - 1; l != r;)
        {
            if (h[l] < h[r])
            {
                rst = max(rst , (r - l) * h[l]);
                ++l;
                continue;
            }

            rst = max(rst, (r - l) * h[r]);
            --r;
        }

        return rst;
    }
};


class SolutionNlogN {
public:
    int maxArea(vector<int>& hs) {
        int l = hs.size();

        vector<pii> hps;///[(height,position)]
        map<int,int> p2h; ///position to height

        FOR(i,l)
        {
            hps.push_back(pii(hs[i],i));
            p2h[i] = hs[i];
        }

        sort (hps.begin(), hps.end());

        int rst = 0;

        for (auto [h,p] : hps)
        {
            auto [p1,h1] = *p2h.begin();
            auto [p2,h2] = *p2h.rbegin();
            int now = max(p - p1, p2 - p) * h;
            rst = max(rst, now);

            p2h.erase(p);
        }

        return rst;
    }
};

class SolutionN2
{
public:
    int maxArea(vector<int>& h)
    {
        int l = h.size();
        int rst = 0;
        FOR(i,l)ffor(j,i+1,l)
        {
            rst = max(rst, (j - i) * min(h[j],h[i]));
        }
        return rst;
    }
};


int main ()
{
    vector<vi> xs{
        {1,8,6,2,5,4,8,3,7},
        {
            1,3,2,5,25,24,5
        }
    };

    for (auto & x : xs)
        print (Solution().maxArea(x));
    return 0;
}
