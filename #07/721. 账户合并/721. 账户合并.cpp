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
给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素 accounts[i][0] 是 名称 (name)，其余元素是 emails 表示该账户的邮箱地址。

现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于同一个人。请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为人们可能具有相同的名称。一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。

合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是按顺序排列的邮箱地址。账户本身可以以任意顺序返回。

 

示例 1：

输入：
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
输出：
[["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
解释：
第一个和第三个 John 是同一个人，因为他们有共同的邮箱地址 "johnsmith@mail.com"。
第二个 John 和 Mary 是不同的人，因为他们的邮箱地址没有被其他帐户使用。
可以以任何顺序返回这些列表，例如答案 [['Mary'，'mary@mail.com']，['John'，'johnnybravo@mail.com']，
['John'，'john00@mail.com'，'john_newyork@mail.com'，'johnsmith@mail.com']] 也是正确的。
 

提示：

accounts的长度将在[1，1000]的范围内。
accounts[i]的长度将在[1，10]的范围内。
accounts[i][j]的长度将在[1，30]的范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/accounts-merge
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


class Solution {///112ms 99.22% 24.9M 92.00%
    using vi = vector<int>;
    class UFSet
    {
        vi father, level;
    public:
        UFSet (int n): father(n), level(n, 0)
        {
            FOR(i,n) father[i] = i;
        }
        int find (int i)
        {
            return father[i] == i ? i : father[i] = find(father[i]);
        }
        void unite (int i, int j)
        {
            i = find(i), j = find(j);
            if (i == j) return;
            if (level[i] < level[j]) father[i] = j;
            else
            {
                father[j] = i;
                if (level[i] == level[j]) ++level[i];
            }
        }
        bool same (int i, int j)
        {
            return find(i) == find(j);
        }
    };
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        unordered_map<string, int> mp;
        UFSet ufs(n);
        FOR(i,n) ffor(j,1,accounts[i].size())
        {
            auto & x = accounts[i][j];
            if (mp.count(x)) ufs.unite(mp[x], i);
            else mp[x] = i;
        }
        vector<pair<string,set<string>>> t(n);
        FOR(i,n)
        {
            auto & [x, y] = t[ufs.find(i)];
            x = accounts[i][0];
            y.insert(begin(accounts[i]) + 1, end(accounts[i]));
        }
        vector<vector<string>> rst;
        for (auto & [x, y] : t) if (!x.empty())
        {
            vector<string> now;
            now.emplace_back(move(x));
            now.insert(end(now), begin(y), end(y));
            rst.emplace_back(move(now));
        }
        return rst;
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<vector<vector<string>>> xs{
        {{"John", "johnsmith@mail.com", "john00@mail.com"}, {"John", "johnnybravo@mail.com"}, {"John", "johnsmith@mail.com", "john_newyork@mail.com"}, {"Mary", "mary@mail.com"}}
    };
    for (auto & x : xs)
        print(x), print(Solution().accountsMerge(x)), print("===");
    return 0;
}
#endif
