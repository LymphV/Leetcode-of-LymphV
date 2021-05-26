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
请考虑一棵二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。



举个例子，如上图所示，给定一棵叶值序列为 (6, 7, 4, 9, 8) 的树。

如果有两棵二叉树的叶值序列是相同，那么我们就认为它们是 叶相似 的。

如果给定的两个根结点分别为 root1 和 root2 的树是叶相似的，则返回 true；否则返回 false 。

 

示例 1：



输入：root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
输出：true
示例 2：

输入：root1 = [1], root2 = [1]
输出：true
示例 3：

输入：root1 = [1], root2 = [2]
输出：false
示例 4：

输入：root1 = [1,2], root2 = [2,2]
输出：true
示例 5：



输入：root1 = [1,2,3], root2 = [1,3,2]
输出：false
 

提示：

给定的两棵树可能会有 1 到 200 个结点。
给定的两棵树上的值介于 0 到 200 之间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/leaf-similar-trees
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///0ms 100.00% 12.5M 36.55%
    using pti = pair<TreeNode*, int>;
public:
    TreeNode * dfs (stack<pti> & s)
    {
        int now = 0;
        while (!s.empty())
        {
            auto [p, k] = s.top();
            if (now < 1)
            {
                auto np = p->left;
                int nk = 1;
                if (np)
                {
                    s.emplace(np, nk);
                    if (!np->left && !np->right) return np;
                    now = 0;
                    continue;
                }
            }
            if (now < 2)
            {
                auto np = p->right;
                int nk = 2;
                if (np)
                {
                    s.emplace(np, nk);
                    if (!np->left && !np->right) return np;
                    now = 0;
                    continue;
                }
            }
            now = k;
            s.pop();
        }
        return 0;
    }
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        stack<pti> a, b;
        a.emplace(root1, 2), b.emplace(root2, 2);
        auto p1 = root1;
        auto p2 = root2;
        if (!p1->left && !p1->right && !p2->left && !p2->right) return p1->val == p2->val;
        while (((p1 = dfs(a)) || 1) && ((p2 = dfs(b)) || 1) && p1 && p2)
            if (p1->val != p2->val) return 0;
        return p1 == p2;
    }
};

#if defined(LocalLymphV)
int main()
{
    TreeNode a{2};
    TreeNode b{1,&a,0}, c{2,&a,0};
    print(&a,&b,&c);

    TreeNode d1{7}, d2{4};
    TreeNode e1{6}, e2{2,&d1,&d2}, e3{9}, e4{8};
    TreeNode f1{5,&e1,&e2}, f2{1,&e3,&e4};
    TreeNode g{3,&f1,&f2};
    //TreeNode x;

    stack<pair<TreeNode*, int>> s;
    s.emplace(&g,2);
    auto p = &g;
    while (p = Solution().dfs(s)) print (p->val);

    vector<pair<TreeNode*,TreeNode*>> xs{
        {&b, &c}
    };
    for (auto & [x, y] : xs)
        print(x,y), print(Solution().leafSimilar(x,y)), print("===");
    return 0;
}
#endif
