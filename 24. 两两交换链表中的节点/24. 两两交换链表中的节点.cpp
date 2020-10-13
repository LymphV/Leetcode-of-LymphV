#include <LymphV>
/**
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例:

给定 1->2->3->4, 你应该返回 2->1->4->3.

来源：力扣（LeetCode）
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
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
class Solution {///4ms 65.58% 7.6M 5.05%
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        auto a = head;
        auto b = a->next;
        auto c = b->next;
        b->next = a;
        a->next = swapPairs(c);
        return b;
    }
};

int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x, Solution().(x));
    return 0;
}
