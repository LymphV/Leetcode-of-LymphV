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
给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。

 

示例 1：


输入：root = [10,5,15,3,7,null,18], low = 7, high = 15
输出：32
示例 2：


输入：root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
输出：23
 

提示：

树中节点数目在范围 [1, 2 * 104] 内
1 <= Node.val <= 105
1 <= low <= high <= 105
所有 Node.val 互不相同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/range-sum-of-bst
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
class Solution {
    int state, rst, l, r;

    bool dfs (TreeNode * root)
    {
        if (!root) return 0;
        int select = -1;
        if (!state)
        {
            if (root->val == l) state = 1, select = 0;
            else if (root->val < l)
            {
                select = 1;
                if (dfs(root->right)) return 1;
            }
            else
            {
                select = 0;
                if (dfs(root->left)) return 1;
                if (!state) state = 1;
            }
        }
        if (state)
        {
            if (select < 0 && dfs(root->left)) return 1;
            if (select < 1)
            {
                if (r < root->val) return 1;
                rst += root->val;
                if (dfs(root->right)) return 1;
            }
        }
        return 0;
    }
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        l = low, r = high, rst = 0, state = 0;
        dfs(root);
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
