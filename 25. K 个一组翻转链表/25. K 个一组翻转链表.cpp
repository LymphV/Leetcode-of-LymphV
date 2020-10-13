#include <iostream>

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


#include <LymphV>
/**
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

 

示例：

给你这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

 

说明：

你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-nodes-in-k-group
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class Solution {///28ms 61.63% 11.3M 5.09%
    using pnn = pair<ListNode*, ListNode*>;
public:
    pnn rvs (ListNode * head, ListNode * tail)
    {
        auto a = head;
        auto c = tail->next;
        while (tail != c)
        {
            auto b = a->next;
            a->next = c;
            c = a;
            a = b;
        }
        return {tail, head};
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;

        ListNode hair{0,head};
        auto now = &hair;

        for(;;)
        {
            auto tail = now;
            FOR(i,k)
            {
                tail = tail->next;
                if (!tail) return hair.next;
            }

            tie(head, tail) = rvs(head,tail);
            now->next = head;
            now = tail;
            head = tail->next;
        }
        return hair.next;
    }
};



int main()
{
    ListNode a(1);
    ListNode b{2,&a};

    print("hh",1,2);


    vector<ListNode*> xs{&b};
    for (auto x : xs)
        print(x),print(Solution().reverseKGroup(x,2));
    return 0;
}
