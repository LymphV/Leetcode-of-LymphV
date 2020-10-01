#include <LymphV>

/**

����һ������ n ������������ nums���ж� nums ���Ƿ��������Ԫ�� a��b��c ��ʹ�� a + b + c = 0 �������ҳ��������������Ҳ��ظ�����Ԫ�顣

ע�⣺���в����԰����ظ�����Ԫ�顣



ʾ����

�������� nums = [-1, 0, 1, 2, -1, -4]��

����Ҫ�����Ԫ�鼯��Ϊ��
[
  [-1, 0, 1],
  [-1, -1, 2]
]*/

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///84ms 19.8M
public:
    vector<vector<int>> threeSum(vector<int>& ns) {
        sort(begin(ns),end(ns));


        int n = ns.size();
        vector<vector<int>> rst;
        FOR(i,n-2)
        {
            if (i && ns[i] == ns[i-1]) continue;
            for (int j = i + 1, k = n - 1; j < k; ++j)
            {
                if (i + 1 < j && ns[j] == ns[j-1]) continue;
                int target = - ns[i] - ns[j];
                if (target < ns[j]) break;

                for (; j < k && target < ns[k]; --k);
                if (j == k) break;

                if (target == ns[k]) rst.push_back({ns[i], ns[j],target});
            }
        }
        return rst;
    }
};

class SolutionV4 {///284ms 20.3M
public:
    vector<vector<int>> threeSum(vector<int>& ns) {
        sort(begin(ns),end(ns));


        unordered_map<int,int> mp;
        int n = ns.size();
        FOR(i,n) mp[ns[i]] = i;
        vector<vector<int>> rst;
        FOR(i,n-2)
        {
            if (i && ns[i] == ns[i-1]) continue;
            ffor(j,i+1,n-1)
            {
                if (i + 1 < j && ns[j] == ns[j-1]) continue;
                int target = - ns[i] - ns[j];
                if (target < ns[j]) break;
                auto obj = mp.find(target);
                if (obj == mp.end()) continue;
                if (j < obj->second) rst.push_back({ns[i], ns[j],obj->first});
            }
        }
        return rst;
    }
};

class SolutionV3 {///720ms 20.6M
public:
    vector<vector<int>> threeSum(vector<int>& ns) {
        sort(begin(ns),end(ns));


        unordered_map<int,int> mp;
        int n = ns.size();
        FOR(i,n) mp[ns[i]] = i;
        vector<vector<int>> rst;
        FOR(i,n-2)
        {
            if (i && ns[i] == ns[i-1]) continue;
            ffor(j,i+1,n-1)
            {
                if (i + 1 < j && ns[j] == ns[j-1]) continue;
                auto obj = mp.find(- ns[i] - ns[j]);
                if (obj == mp.end()) continue;
                if (j < obj->second) rst.push_back({ns[i], ns[j],obj->first});
            }
        }
        return rst;
    }
};



class SolutionV2 {///792ms 26.5M
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int,int> mp;
        FOR(i,int(nums.size())) ++mp[nums[i]];
        vector<int> ns;
        for (auto [x, y] : mp)
            FOR(i,min(y,3)) ns.push_back(x);

        mp.clear();
        int n = ns.size();
        FOR(i,n)
            mp[ns[i]] = i;
        set<vector<int>> rst;
        FOR(i,n-2)ffor(j,i+1,n-1)
        {
            auto obj = mp.find(- ns[i] - ns[j]);
            if (obj == mp.end()) continue;
            if (j < obj->second) rst.insert({ns[i], ns[j],obj->first});
        }
        return vector<vector<int>>{begin(rst), end(rst)};
    }
};


class SolutionV1 {///1632ms 27M
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        map<int,int> mp;
        FOR(i,int(nums.size())) ++mp[nums[i]];
        vector<int> ns;
        for (auto [x, y] : mp)
            FOR(i,min(y,3)) ns.push_back(x);

        mp.clear();
        int n = ns.size();
        FOR(i,n)
            mp[ns[i]] = i;
        set<vector<int>> rst;
        FOR(i,n-2)ffor(j,i+1,n-1)
        {
            auto obj = mp.find(- ns[i] - ns[j]);
            if (obj == mp.end()) continue;
            if (j < obj->second) rst.insert({ns[i], ns[j],obj->first});
        }
        return vector<vector<int>>{begin(rst), end(rst)};
    }
};

int main ()
{
    vector<vi> xs{
        {-1,0,1,2,-1,-4},
        {}
    };

    for(auto x : xs)
        print(x,Solution().threeSum(x));
    return 0;
}
