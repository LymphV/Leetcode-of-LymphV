#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
///python.print(list)

std::ostream & operator<< (std::ostream & out, ListNode l)
{
    out << "[";
    auto p = &l;
    for (; p; p = p->next)
        out << "(" << p->val << ", " << p->next << ")" << (p->next ? ", " : "");
    return out << "]";
}
std::ostream & operator<< (std::ostream & out, ListNode * l)
{
    return out << *l;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x = 0, TreeNode * left = 0, TreeNode * right = 0) : val(x), left(left), right(right) {}
    /*~TreeNode ()
    {
        delete left;
        delete right;
    }*/
};


