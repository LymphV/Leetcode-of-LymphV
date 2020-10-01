#include <LymphV>
/**
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */



using vit = vector<int>::iterator;
class Solution {
public:
    vit find (vit l, vit r, int x)
    {
        vit rst = l;
        for (;rst != r && *rst != x; ++rst);
        return rst;
    }
    TreeNode* f (vit inb, vit ine, vit pob, vit poe)
    {
        if (inb == ine) return NULL;
        int root = *--poe;
        vit mid = find(inb,ine,root);
        return new TreeNode{
                        root,
                        f (inb, mid, pob, pob + (mid - inb)),
                        f (mid + 1, ine, pob + (mid - inb), poe)
                    };
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return f(begin(inorder), end(inorder), begin(postorder), end(postorder));
    }

};

int main ()
{

    return 0;
}
