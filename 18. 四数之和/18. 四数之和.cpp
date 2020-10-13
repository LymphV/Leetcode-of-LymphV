#include <LymphV>
/**
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，
使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
using pii = pair<int,int>;
class Solution///188ms 6.74% 26.1M 5.01%
{
public:
    vector<vector<int>> fourSum(vector<int>& ns, int target)
    {
        int n = ns.size();
        if (n < 4) return vector<vector<int>> ();

        sort(begin(ns), end(ns));
        unordered_map<int,vector<pii>> mp;
        vector<vector<int>> rst;
        FOR(i,n)
        {
            int x = ns[i];
            if (i && x == ns[i - 1])
            {
                ffor(j,i+1,n)
                {
                    int y = ns[j];
                    if (i + 1 < j && y == ns[j - 1]) continue;

                    if (mp.count(target - x - y))
                    for (auto [p, q] : mp[target - x - y])
                        if (q == i - 1) rst.push_back({ns[p],ns[q],x,y});
                }
            }
            else ffor(j,i+1,n)
            {
                int y = ns[j];
                if (i + 1 < j && y == ns[j - 1]) continue;

                if (mp.count(target - x - y))
                    for (auto [p, q] : mp[target - x - y])
                        if (q < i) rst.push_back({ns[p],ns[q],x,y});
                mp[x + y].push_back(pii(i, j));
            }
        }
        return rst;
    }
};



class SolutionV3 {///236 ms5.03% 26.2 MB5.06%
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 4) return vector<vector<int>>();

        sort(begin(nums), end(nums));
        unordered_map<int,vector<pii>> mp;
        for (int i = n - 2; 0 <= i; --i)
        {
            int x = nums[i];
            if (i < n - 2 && x == nums[i + 1])
            {
                if (x != nums[i + 2])
                    mp[2 * x].push_back(pii(i,i+1));
                continue;
            }
            for (int j = n - 1; i < j; --j)
            {
                int y = nums[j];
                if (j < n - 1 && y == nums[j + 1]) continue;
                mp[x + y].push_back(pii(i,j));
            }
        }

        vector<vector<int>> rst;
        FOR(i,n)
        {
            int x = nums[i];
            if (i && x == nums[i - 1]) continue;
            ffor(j,i+1,n)
            {
                int y = nums[j];
                if (i + 1 < j && y == nums[j - 1]) continue;

                auto obj = mp.find(target - x - y);
                if (obj == end(mp)) continue;
                for (auto [p, q] : obj->second)
                {
                    if (j < p) rst.push_back({x,y,nums[p],nums[q]});
                    else break;
                }
            }
        }
        return rst;
    }
};


class SolutionV2 {///168 ms 10.15% 26.3 MB 5.06%
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 4) return vector<vector<int>>();

        sort(begin(nums), end(nums));
        unordered_map<int,vector<pii>> mp;
        for (int j = n - 1; j; --j)
        {
            int y = nums[j];
            if (j < n - 1 && y == nums[j + 1]) continue;
            for (int i = j - 1; 0 <= i; --i)
            {
                int x = nums[i];
                if (i < j - 1 && x == nums[i + 1]) continue;
                mp[x + y].push_back(pii(i,j));
            }
        }

        vector<vector<int>> rst;
        FOR(i,n)
        {
            int x = nums[i];
            if (i && x == nums[i - 1]) continue;
            ffor(j,i+1,n)
            {
                int y = nums[j];
                if (i + 1 < j && y == nums[j - 1]) continue;

                auto obj = mp.find(target - x - y);
                if (obj == end(mp)) continue;
                for (auto [p, q] : obj->second)
                {
                    if (j < p) rst.push_back({x,y,nums[p],nums[q]});
                }
            }
        }
        return rst;
    }
};


class SolutionV1 {///216 ms 5.03% 35.7 MB 5.06%
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        int n = nums.size();
        unordered_map<int,map<pii,pii>> mp;
        FOR(i,n)ffor(j,i+1,n)
            mp[nums[i]+nums[j]][pii(nums[i],nums[j])] = pii(i,j);

        vector<vector<int>> rst;
        FOR(i,n)
        {
            int x = nums[i];
            if (i && x == nums[i - 1]) continue;
            ffor(j,i+1,n)
            {
                int y = nums[j];
                if (i + 1 < j && y == nums[j - 1]) continue;

                auto obj = mp.find(target - x - y);
                if (obj == end(mp)) continue;
                for (auto [k, v] : obj->second)
                {
                    auto [z, w] = k;
                    auto [p, q] = v;
                    if (j < p) rst.push_back({x,y,z,w});
                }
            }
        }
        return rst;
    }
};





int main()
{
    vector<pair<vi,int>> xs{
        {{1, 0, -1, 0, -2, 2},0},
        {{},0},
        {{5,5,3,5,1,-5,1,-2},4},
        {{-1,2,2,-5,0,-1,4},3},
        {{0,1,5,0,1,5,5,-4},11}
        };
    for (auto [x,y] : xs)
        print(x,y, Solution().fourSum(x,y));
    return 0;
}
