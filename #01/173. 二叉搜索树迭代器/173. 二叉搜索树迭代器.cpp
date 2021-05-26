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
实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。
注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。

你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。

 

示例：


输入
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
[null, 3, 7, true, 9, true, 15, true, 20, false]

解释
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // 返回 3
bSTIterator.next();    // 返回 7
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 9
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 15
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 20
bSTIterator.hasNext(); // 返回 False
 

提示：

树中节点的数目在范围 [1, 105] 内
0 <= Node.val <= 106
最多调用 105 次 hasNext 和 next 操作
 

进阶：

你可以设计一个满足下述条件的解决方案吗？next() 和 hasNext() 操作均摊时间复杂度为 O(1) ，并使用 O(h) 内存。其中 h 是树的高度。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-search-tree-iterator
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


class BSTIterator {///28ms 90.45% 23.4M 81.35%
    stack<TreeNode*> st;
    TreeNode * now;
public:
    bool hasNext() {
        return now || !st.empty();
    }
    BSTIterator(TreeNode* root) : now(root) {
    }

    int next() {
        while (now)
        {
            st.push(now);
            now = now->left;
        }
        now = st.top();
        st.pop();
        int rst = now->val;
        now = now->right;
        return rst;
    }

};


class BSTIteratorV1 {///40ms 41.02% 23.4M 95.52%
    stack<pair<int, TreeNode*>> st;
public:
    bool hasNext() {
        while (!st.empty())
        {
            if (st.top().first == 1) break;
            if (!st.top().second || !st.top().first)
            {
                st.pop();
                if (!st.empty())--st.top().first;
            }
            else st.push(make_pair(2,st.top().second->left));
        }
        return !st.empty();

    }
    BSTIteratorV1(TreeNode* root) {
        st.push(make_pair(2, root));
        hasNext();
    }

    int next() {
        int rst = st.top().second->val;
        st.push(make_pair(2, st.top().second->right));
        hasNext();
        return rst;
    }

};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

#if defined(LocalLymphV)
int main()
{
    TreeNode a(3), b(9), c(20);
    TreeNode d(15, &b, &c);
    TreeNode e(7, &a, &d);
    vector<TreeNode*> xs{&d, &e};
    print(d.right->val);
    for (auto x : xs)
    {
        print(x->val);
        BSTIterator it(x);
        while (it.hasNext())
            print(it.hasNext(),it.next());
        print("===");
    }
    return 0;
}
#endif
