#include <LymphV>
/**给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n 保证是有效的。

进阶：

你能尝试使用一趟扫描实现吗？



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
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
class Solution { ///8ms 52.55% 10.4M 5.19%
public:
    int cnt = 0;
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) return head;
        head->next = removeNthFromEnd(head->next, n);
        if (++cnt == n) return head->next;
        return head;
    }
};


int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x, Solution().(x));
    return 0;
}
