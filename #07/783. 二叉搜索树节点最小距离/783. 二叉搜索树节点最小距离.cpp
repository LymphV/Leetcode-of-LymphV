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
给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。

注意：本题与 530：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/ 相同

 

示例 1：


输入：root = [4,2,6,1,3]
输出：1
示例 2：


输入：root = [1,0,48,null,null,12,49]
输出：1
 

提示：

树中节点数目在范围 [2, 100] 内
0 <= Node.val <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
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

class Solution {///0ms 100.00% 9.5M 50.45%
    int rst;
    int solve (TreeNode* root, int & a, int & b)
    {
        if (!root) return rst;
        int la = -1000000, lb = 1000000, ra = -1000000, rb = 1000000;
        solve(root->left, la, lb), solve(root->right, ra, rb);

        a = max(root->val, ra), b = min(root->val, lb);
        return rst = min({rst, root->val - la, rb - root->val});
    }
public:
    int minDiffInBST(TreeNode* root) {
        rst = 1000000;
        int a = -1000000, b = 1000000;
        return solve(root, a, b);
    }
};


class SolutionV1 {///8ms 15.03% 14.2M 5.14%
    using vi = vector<int>;
    vi solve (TreeNode * root)
    {
        if (!root) return vi{-1000000, 1000000, 1000000};
        vi a = solve(root->left), b = solve(root->right);
        return vi{max(b[0], root->val), min(a[1], root->val), min({a[2], b[2], root->val - a[0], b[1] - root->val})};
    }
public:
    int minDiffInBST(TreeNode* root) {
        return solve(root)[2];
    }
};

#if defined(LocalLymphV)
int main()
{
    TreeNode a{29};
    TreeNode b{52, &a, 0};
    TreeNode c{13, 0, &b};
    TreeNode d{12, 0, &c};
    vector<TreeNode *> xs{ &d};
    for (auto x : xs)
        print(x), print(Solution().minDiffInBST(x)), print("===");
    return 0;
}
#endif
