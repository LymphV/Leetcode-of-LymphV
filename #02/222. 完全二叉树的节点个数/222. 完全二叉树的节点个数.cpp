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
给出一个完全二叉树，求出该树的节点个数。

说明：

完全二叉树的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。

示例:

输入:
    1
   / \
  2   3
 / \  /
4  5 6

输出: 6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-complete-tree-nodes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///52ms 74.32% 31M 17.15%
    int getLevel (TreeNode * root, int child, int level = 0)
    {
        if (!child) for (;root->left; root = root->left, ++level);
        else for (; root->right; root = root->right, ++level);
        return level;
    }
    int getNode (TreeNode * root, int left = -1, int right = -1)
    {
        if (!root) return 0;
        int l = ~left ? left : getLevel(root, 0), r = ~right ? right : getLevel(root, 1);
        if (l == r) return (1 << (l + 1)) - 1;
        int m = getLevel(root->left, 1) + 1;
        if (m == r) return (1 << r) + getNode(root->left, l - 1);
        return (1 << l) + getNode(root->right, -1, r - 1);
    }
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return getNode(root);
    }
};

class SolutionV2 {///72ms 9.84% 30.9M 22.23%
    int getLevel (TreeNode * root, int child, int level = 0)
    {
        if (!child) for (;root->left; root = root->left, ++level);
        else for (; root->right; root = root->right, ++level);
        return level;
    }
    int getNode (TreeNode * root)
    {
        if (!root) return 0;
        int l = getLevel(root, 0), r = getLevel(root, 1);
        if (l == r) return (1 << (l + 1)) - 1;
        int m = getLevel(root->left, 1) + 1;
        if (m == r) return (1 << r) + getNode(root->left);
        return (1 << l) + getNode(root->right);
    }
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return getNode(root);
    }
};

class SolutionV1 {///56ms 55.72% 31.2M 8.11%
    int nLevel, nNode;
    void dfs (TreeNode * root, int level = 0)
    {
        if (!nNode)
        {
            if (!root->left) nNode = 1, nLevel = level;
            else
            {
                dfs(root->left, level + 1);
                dfs(root->right, level + 1);
            }
        }
        else
        {
            if (level < nLevel)
            {
                dfs(root->left, level + 1);
                dfs(root->right, level + 1);
            }
            else
            {
                if (root) ++nNode;
                else throw 1;
            }
        }
    }
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        nLevel = 0, nNode = 0;
        try {dfs(root);}
        catch (int){;}
        return (1 << nLevel) - 1 + nNode;
    }
};


#if defined(LocalLymphV)
int main()
{
    TreeNode a(4), b(5), c(6), d(7);
    TreeNode e(2,&a,&b), f(3,&c,&d);
    TreeNode g(1,&e,&f);
    vector<TreeNode *> xs{&g, &e};
    for (auto x : xs)
        print(x), print(Solution().countNodes(x)), print("===");
    return 0;
}
#endif
