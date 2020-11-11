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
给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。

例如，从根到叶子节点路径 1->2->3 代表数字 123。

计算从根到叶子节点生成的所有数字之和。

说明: 叶子节点是指没有子节点的节点。

示例 1:

输入: [1,2,3]
    1
   / \
  2   3
输出: 25
解释:
从根到叶子节点路径 1->2 代表数字 12.
从根到叶子节点路径 1->3 代表数字 13.
因此，数字总和 = 12 + 13 = 25.
示例 2:

输入: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
输出: 1026
解释:
从根到叶子节点路径 4->9->5 代表数字 495.
从根到叶子节点路径 4->9->1 代表数字 491.
从根到叶子节点路径 4->0 代表数字 40.
因此，数字总和 = 495 + 491 + 40 = 1026.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-root-to-leaf-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///4ms 81.75% 12.4M 25.48%
public:
    int sumNumbers(TreeNode* root, int now = 0) {
        if (!root) return 0;
        now = now * 10 + root->val;
        if (!root->left && !root->right) return now;
        int rst = 0;
        if (root->left) rst += sumNumbers(root->left, now);
        if (root->right) rst += sumNumbers(root->right, now);
        return rst;
    }
};


#if defined(LocalLymphV)
int main()
{
    TreeNode a{2,0,0}, b{3,0,0};
    TreeNode c{1,&a,&b};
    vector<TreeNode*> xs{&a,&b,&c};
    for (auto x : xs)
        print(x), print(Solution().sumNumbers(x)), print("===");
    return 0;
}
#endif
