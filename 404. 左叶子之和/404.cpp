/****************

���������������������Ҷ��֮�͡�

ʾ����

    3
   / \
  9  20
    /  \
   15   7

������������У���������Ҷ�ӣ��ֱ��� 9 �� 15�����Է��� 24



*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int rst = 0;
        if (root)
        {
            if (root -> left)
            {
                if (ifLL(root -> left))
                    rst += root -> left -> val;
                else
                    rst += sumOfLeftLeaves(root -> left);
            }
            if (root -> right)
                rst += sumOfLeftLeaves(root -> right);
        }
        return rst;
    }

    int ifLL (TreeNode * node)
    {
        return !node -> left && !node -> right;
    }
};
