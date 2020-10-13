#if defined(LocalLymphV)
#include "../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。

 

示例：

输入：

   1
    \
     3
    /
   2

输出：
1

解释：
最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。
 

提示：

树中至少有 2 个节点。
本题与 783 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/ 相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)



class Solution {///28ms 82.12% 24.6M 56.06%
    auto dfs (TreeNode * root)
    {
        if (!root) return make_tuple(INT_MAX,INT_MAX,INT_MIN);///最小差，最小值，最大值
        int rst = INT_MAX, mn = root->val, mx = root->val;
        int a, b, c;
        if (root->left)
        {
            tie(a, b, c) = dfs(root->left);
            rst = min({a, rst, abs(root->val - c)});
            mn = b;
        }
        if (root->right)
        {
            tie (a, b, c) = dfs(root->right);
            rst = min({a, rst, abs(root->val - b)});
            mx = c;
        }
        return make_tuple(rst, mn, mx);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        return get<0>(dfs(root));
    }
};


#if defined(LocalLymphV)
int main()
{
    TreeNode a{2,0,0};
    TreeNode b{3,&a,nullptr};
    TreeNode c{1,nullptr,&b};

    TreeNode d1{445,0,0}, d2{699,0,0};
    TreeNode e1{384,0,&d1}, e2{652,0,&d2};
    TreeNode f{543,&e1,&e2};

    vector<TreeNode *> xs{&c,&f};
    for (auto x : xs)
        print(x), print(Solution().getMinimumDifference(x)), print("===");
    return 0;
}
#endif
